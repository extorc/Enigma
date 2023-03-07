#include <iostream>
#include "Frame.h"
#include "Graphics.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/glm.hpp"
#include <vector>
#include "Renderer.h"
#include "Blit.h"
#include "glm/gtc/matrix_transform.hpp"

int main(){
	Window window = createWindow();
	Frame frame = createTexture();
	std::vector<glm::vec4> pixels;

	int image_height = window.height;
	int image_width = window.width;

	glm::vec3 origin(0.0f, 0.0f, 3.0f);
	glm::vec3 sphere(0.0f, 0.0f, -1.0f);
	glm::vec3 objectColor(1, 0, 1);

	while(!glfwWindowShouldClose(window.window)){
		pixels.clear();

		for(int j = 0; j < image_height; j++){
			for(int i = 0; i < image_width; i++){
				glm::vec2 ndc((float)i/(float)image_width, (float)j/(float)image_height); //Z coord only changes FOV
				glm::vec2 screen = ndc * 2.0f - 1.0f; 

				glm::vec4 target = glm::vec4(screen, 2.5f, 1);
				glm::vec3 ray = glm::vec3(glm::inverse(glm::lookAt(origin, origin + glm::vec3(0, 0, -1), glm::vec3(0, -1, 0))) * glm::vec4(glm::normalize(glm::vec3(target) / target.w), 0));
				
				pixels.push_back(processPixel(origin, glm::normalize(ray), sphere, objectColor));
			}
		}
		blitFrame(frame, image_width, image_height, pixels);
		glfwSwapBuffers(window.window);
		glfwPollEvents();
	}
	glfwTerminate();
}
