#include "Enigma.h"

#define DX 700
#define DY 700

int main(){
	Window window = createWindow(DX, DY);
	Frame frame = createTexture();
	Scene scene;
	Camera camera({0, 0, 5}, DX, DY);
	Renderer renderer(camera, &scene);
	int sampleCount = 1;
	int maxSampleCount = 30;
	bool doneRendering = false;

	scene.objects.push_back(std::unique_ptr<Object>(new Plane({0, 0, 0}, {0, -1.5f, 0}, {0, 1, 0}, 0)));
	scene.objects.push_back(std::unique_ptr<Object>(new Sphere({ 0   , 0.5f, -1}, 1.5f, 1)));
	scene.objects.push_back(std::unique_ptr<Object>(new Sphere({-3.5f, 0.5f, -1}, 1.5f, 2)));
	scene.objects.push_back(std::unique_ptr<Object>(new Sphere({ 3.5f, 0.5f, -1}, 1.5f, 3)));

	scene.materialList.push_back({0.1f, .2f, {0, 0, 1}});
	scene.materialList.push_back({0.5f, 0.5f  , {1, 0, 0.5f}});
	scene.materialList.push_back({1, 0  , {1, 0, 0.5f}});
	scene.materialList.push_back({0, 1  , {1, 0, 0.5f}});

	std::vector<glm::vec4> pixels(camera.u * camera.v, glm::vec4(0));                                  //Create buffers for pixel and accumulation data
	std::vector<glm::vec4> accumulation(camera.u * camera.v, glm::vec4(0));

	int image_height = window.height;
	int image_width = window.width;

	double startTime = glfwGetTime();
	camera.calculateRayDirections();

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
		blitFrame(frame, image_width, image_height, pixels);
		glfwSwapBuffers(window.window);
		glfwPollEvents();
	}
	glfwTerminate();
}
