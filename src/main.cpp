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
	scene.spheres.push_back({{0, -101.5f, -1}, 100.0f, {0, 0, 1}});
	scene.spheres.push_back({{0, 0.5f, -1}, 2.0f, {1, 0, 0.5f}});
	scene.spheres[1].mat.roughness = 1;

	Camera camera({0, 0, 5}, 500, 500);
	Renderer renderer(camera, scene);
	std::vector<glm::vec4> pixels;

	int image_height = window.height;
	int image_width = window.width;

	camera.calculateRayDirections();
	while(!glfwWindowShouldClose(window.window)){
		pixels.clear();
		camera.cameraInput(window.window);	
		for(int j = 0; j < image_height; j++){
			for(int i = 0; i < image_width; i++){
				Ray ray = {glm::normalize(camera.rayDirections[j * image_width + i]), camera.cameraPosition};
				pixels.push_back(renderer.processPixel(ray));
			}
		}
		camera.calculateRayDirections();
		blitFrame(frame, image_width, image_height, pixels);
		glfwSwapBuffers(window.window);
		glfwPollEvents();
	}
	glfwTerminate();
}
