#include "Enigma.h"

#define DX 480
#define DY 480

int main(){
	float vertices[] = {
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 0.0f
	};
	Window window = createWindow(DX, DY);
	Scene scene;
	Camera camera({0, 5, 10}, DX, DY);
	camera.rotateCamera(0.5f, 0);
	Renderer renderer(camera, &scene);

	GLuint frameBuffer;
	glCreateTextures(GL_TEXTURE_2D, 1, &frameBuffer);
	glTextureParameteri(frameBuffer, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(frameBuffer, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(frameBuffer, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(frameBuffer, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureStorage2D(frameBuffer, 1, GL_RGBA32F, DX, DY);
	glBindImageTexture(0, frameBuffer, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
	
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	const char* vertexShaderSource = R"(
		#version 460 core
		layout(location = 0) in vec3 aPos;
		layout(location = 1) in vec2 uv;

		out vec2 UV;

		void main() {
			gl_Position = vec4(aPos, 1.0);
			UV = uv;
		})";

	const char* fragmentShaderSource = R"(#version 460 core
		out vec4 FragColor;
		uniform sampler2D screen;
		in vec2 UV;
		
		void main() {
			FragColor = texture(screen, UV);
		})";

	const char* computeShaderSource = R"(#version 460 core
		layout(local_size_x = 8, local_size_y = 4, local_size_z = 1) in;
		layout(rgba32f, binding = 0) uniform image2D screen;
		void main(){
			imageStore(screen, ivec2(gl_GlobalInvocationID.xy), vec4(1.0, 0.5, 0.5, 1.0));
		})";

	unsigned int vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLuint computeShader = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(computeShader, 1, &computeShaderSource, NULL);
	glCompileShader(computeShader);
	checkShaderCompilation(computeShader, GL_COMPUTE_SHADER);

	GLuint computeProgram = glCreateProgram();
	glAttachShader(computeProgram, computeShader);
	glLinkProgram(computeProgram);
	
	int sampleCount = 1;
	int maxSampleCount = 30;
	bool doneRendering = false;

	scene.objects.push_back(std::unique_ptr<Object>(new Plane({0, 0, 0}, {0, -1.5f, 0}, {0, 1, 0}, 0)));
	scene.objects.push_back(std::unique_ptr<Object>(new Sphere({ 0   , 0.5f, -1}, 1.5f, 1)));
	scene.objects.push_back(std::unique_ptr<Object>(new Sphere({-3.5f, 0.5f, -1}, 1.5f, 2)));
	scene.objects.push_back(std::unique_ptr<Object>(new Sphere({ 3.5f, 0.5f, -1}, 1.5f, 3)));
	scene.objects.push_back(std::unique_ptr<Object>(new Triangle({
		glm::vec3(0, 1, 2), 
		glm::vec3(2, 1, 2),
		glm::vec3(2, 3, 2),
		1
	})));
	scene.objects.push_back(std::unique_ptr<Object>(new Triangle({
		glm::vec3(0, 1, 2), 
		glm::vec3(2, 3, 2),
		glm::vec3(0, 3, 2),
		2
	})));
	scene.materialList.push_back({0.1f, .2f, {0, 0, 1}});
	scene.materialList.push_back({0.5f, 0.5f  , {1, 0, 0.5f}});
	scene.materialList.push_back({1, 0  , {1, 0, 0.5f}});
	scene.materialList.push_back({0, 1  , {1, 0, 0.5f}});

	std::vector<glm::vec4> pixels(camera.u * camera.v, glm::vec4(0));                              //Create buffers for pixel and accumulation data
	std::vector<glm::vec4> accumulation(camera.u * camera.v, glm::vec4(0));

	int image_height = window.height;
	int image_width = window.width;

	double startTime = glfwGetTime();
	camera.calculateRayDirections();

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cerr << "OpenGL error: " << err << std::endl;
	}
	
	while(!glfwWindowShouldClose(window.window)){
		if(sampleCount < maxSampleCount){
			for(int j = 0; j < image_height; j++){
				for(int i = 0; i < image_width; i++){                                              //For every pixel on the screen
					Ray ray = {
						glm::normalize(camera.rayDirections[j * image_width + i]), 
						camera.cameraPosition
					};                                                                             //Generate a ray
					auto color = renderer.processPixel(ray);                                       //And process the ray
					accumulation[j * camera.u + i] += color;                                       //Accumulate the data processed
					pixels[j * camera.u + i] = accumulation[j * camera.u + i]/(float)sampleCount;  //And update pixel data based on accumulation and sample count
				}
			}
			sampleCount++;
		}
		if(sampleCount == maxSampleCount && !doneRendering){
			std::cout<<"Render time : " << glfwGetTime() - startTime<<std::endl;
			doneRendering = true;
		}
		if(sampleCount < maxSampleCount) std::cout<<sampleCount<<" "<< glfwGetTime() - startTime<<std::endl;

		glUseProgram(computeProgram);
		glBindTextureUnit(0, frameBuffer);
		glUniform1i(glGetUniformLocation(computeProgram, "screen"), 0);
		glDispatchCompute(ceil(DX / 8), ceil(DY / 4), 1);
		glMemoryBarrier(GL_ALL_BARRIER_BITS);

		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window.window);
		glfwPollEvents();
	}
	glfwTerminate();
}
