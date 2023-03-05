#include "Frame.h"
#include "Graphics.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/glm.hpp"
#include <vector>
#include "Renderer.h"

int main(){
	Window window = createWindow();
	Frame frame = createTexture();
	std::vector<glm::vec4> pixels;

	int image_height = window.height;
	int image_width = window.width;

	glm::vec3 origin(0.0f, 0.0f, -5.4f);
	glm::vec3 sphere(0.0f, 0.0f, 9.0f);

	for(int j = 0; j < image_height; j++){
		for(int i = 0; i < image_width; i++){
			glm::vec3 pixel(i-250, j-250, 129.4f); //Z coord only changes FOV
			glm::vec3 ray = pixel - origin;
			pixels.push_back(processPixel(origin, glm::normalize(ray), sphere));
		}
	}

	while(!glfwWindowShouldClose(window.window)){
		blitFrame(frame, image_width, image_height, pixels);
		glfwSwapBuffers(window.window);
		glfwPollEvents();
	}
	glfwTerminate();
}
