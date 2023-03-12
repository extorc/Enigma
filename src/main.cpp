//C++ Std
#include <iostream>
#include <vector>

//Vendor
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

//Enigma
#include "Graphics.h"
#include "Renderer.h"
#include "Blit.h"
#include "Camera.h"
#include "Renderer.h"
#include "Objects/Plane.h"
#include "Objects/Sphere.h"
#include "Utils/Frame.h"
#include "Utils/Ray.h"
#include "Utils/Scene.h"

int main(){
	Window window = createWindow();
	Frame frame = createTexture();

	Scene scene;

	scene.objects.push_back(std::unique_ptr<Object>(new Plane({0, 0, 0}, {0, -1.5f, 0}, {0, 1, 0}, 0)));
	scene.objects.push_back(std::unique_ptr<Object>(new Sphere({0, 0.5f, -1}, 2, 1)));

	scene.materialList.push_back({0.1f, {0, 0, 1}});
	scene.materialList.push_back({1.0f, {1, 0, 0.5f}});

	Camera camera({0, 0, 5}, 500, 500);
	Renderer renderer(camera, &scene);
	std::vector<glm::vec4> pixels;
	pixels.resize(camera.u * camera.v);
	std::fill(pixels.begin(), pixels.end(), glm::vec4(0));
	std::vector<glm::vec4> accumulation;
	accumulation.resize(camera.u * camera.v);
	std::fill(accumulation.begin(), accumulation.end(), glm::vec4(0));

	int image_height = window.height;
	int image_width = window.width;

	int sampleCount = 1;
	camera.calculateRayDirections();
	while(!glfwWindowShouldClose(window.window)){
		camera.cameraInput(window.window);	
		for(int j = 0; j < image_height; j++){
			for(int i = 0; i < image_width; i++){
				Ray ray = {glm::normalize(camera.rayDirections[j * image_width + i]), camera.cameraPosition};
				auto color = renderer.processPixel(ray);
				accumulation[j * camera.u + i] += color;
				pixels[j * camera.u + i] = accumulation[j * camera.u + i]/(float)sampleCount;
			}
		}
		sampleCount++;
		std::cout<<sampleCount<<std::endl;
		camera.calculateRayDirections();
		blitFrame(frame, image_width, image_height, pixels);
		glfwSwapBuffers(window.window);
		glfwPollEvents();
	}
	glfwTerminate();
}
