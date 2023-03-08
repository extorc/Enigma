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

int main(){
	Window window = createWindow();
	Frame frame = createTexture();
	glm::vec3 origin(0.0f, 0.0f, 3.0f);

	Camera camera(origin, 500, 500);
	std::vector<glm::vec4> pixels;

	int image_height = window.height;
	int image_width = window.width;

	glm::vec3 sphere(0.0f, 0.0f, -1.0f);
	glm::vec3 objectColor(1, 0, 1);
	
	camera.calculateRayDirections();
	while(!glfwWindowShouldClose(window.window)){
		pixels.clear();

		for(int j = 0; j < image_height; j++){
			for(int i = 0; i < image_width; i++){
				Ray ray = {glm::normalize(camera.rayDirections[j * image_width + i]), camera.cameraPosition};
				pixels.push_back(processPixel(ray, sphere, objectColor));
			}
		}
		camera.rotateCamera(0.1f, 0.1f);
		camera.translateCamera(glm::vec3(-0.4f, -0.4f, 0));
		camera.calculateRayDirections();
		blitFrame(frame, image_width, image_height, pixels);
		glfwSwapBuffers(window.window);
		glfwPollEvents();
	}
	glfwTerminate();
}
