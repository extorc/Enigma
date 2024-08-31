#include "Enigma.h"

#define DX 500
#define DY 500

int main(){
	float vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 
		-1.0f,  1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		1.0f, 1.0f, 0.0f
	};
	Window window = createWindow(DX, DY);
	Scene scene;
	Camera camera({0, 5, 10}, DX, DY);
	camera.rotateCamera(0.5f, 0);
	Renderer renderer(camera, &scene);

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	const char* vertexShaderSource = R"(
	#version 330 core
	layout(location = 0) in vec3 aPos;

	void main() {
		gl_Position = vec4(aPos, 1.0);
	}
	)";
	const char* fragmentShaderSource = R"(#version 430 core
	out vec4 FragColor;

	layout(std430, binding = 0) buffer PixelColors {
		vec4 pixelColors[];
	};

	void main() {
		ivec2 pixelCoord = ivec2(gl_FragCoord.xy);
		int pixelIndex = pixelCoord.y * 500 + pixelCoord.x;

		if (pixelIndex >= 0 && pixelIndex < 500 * 500) {
			FragColor = pixelColors[pixelIndex];
		} else {
			FragColor = vec4(1.0, 0.0, 0.0, 1.0); // Default to red if out of bounds
		}
	})";

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

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

	unsigned int ssbo;
	glGenBuffers(1, &ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, pixels.size() * sizeof(glm::vec4), NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

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
		 // Update SSBO with latest pixel data
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, pixels.size() * sizeof(glm::vec4), pixels.data());
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window.window);
		glfwPollEvents();
	}
	glfwTerminate();
}
