//C++ Std
#include <iostream>
#include <vector>

//Vendor
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/glm.hpp"

//Enigma
#include "Frame.h"
#include "Graphics.h"
#include "Renderer.h"
#include "Blit.h"
#include "Camera.h"
#include "Ray.h"
#include "Scene.h"
#include "Sphere.h"
#include "Renderer.h"

int main(){
	Window window = createWindow();
	Frame frame = createTexture();

	Scene scene;

	{
		Sphere sphere;
		sphere.radius = 100;
		sphere.position = {0, -101.5f, -1};
		sphere.matIndex = 0;
		scene.spheres.push_back(sphere);

	}
	{
		Sphere sphere;
		sphere.radius = 2;
		sphere.position = {0, 0.5f, -1};
		sphere.matIndex = 1;
		scene.spheres.push_back(sphere);

	}

	scene.materialList.push_back({0.1f, {0, 0, 1}});
	scene.materialList.push_back({1.0f, {1, 0, 0.5f}});

	Camera camera({0, 0, 5}, 500, 500);
	Renderer renderer(camera, scene);
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
