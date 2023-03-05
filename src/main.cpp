#include <cmath>
#include <iostream>
#include "Graphics.h"
#include <fstream>
#include <cstdio>
#include <ostream>
#include <string>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/glm.hpp"
#include <vector>

glm::vec4 processPixel(glm::vec3 rayOrigin, glm::vec3 rayDirection){
	float a = glm::dot(rayDirection, rayDirection);
	float b = 2 * glm::dot(rayDirection, rayOrigin);
	float c = glm::dot(rayOrigin, rayOrigin) - 29.0f;

	float discriminant = (b * b) - 4 * a * c;

	if(discriminant >= 0){
		float quadSol1 = ((b * -1) - std::sqrt(discriminant))/(2 * a);
		float quadSol2 = ((b * -1) + std::sqrt(discriminant))/(2 * a);
		
		float t;
		if(quadSol1 < 0)
			t = quadSol2;
		else
			t = quadSol1;

		glm::vec3 intercept = t * rayDirection + rayOrigin;
		return glm::vec4(intercept, 1.0f);
	}
	else
		return glm::vec4(0.0f);
}
int main(){
	Window window = createWindow();
	Frame frame = createTexture();
	std::vector<glm::vec4> pixels;

	int image_height = window.height;
	int image_width = window.width;

	glm::vec3 origin(0.0f, 0.0f, -5.4f);

	for(int j = 0; j < image_height; j++){
		for(int i = 0; i < image_width; i++){
			glm::vec3 pixel(i-250, j-250, 0);
			glm::vec3 ray = pixel - origin;
			pixels.push_back(processPixel(origin,glm::normalize(ray)));
		}
	}

	while(!glfwWindowShouldClose(window.window)){
		glBindTexture(GL_TEXTURE_2D, frame.texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, image_width, image_height, 0, GL_RGBA, GL_FLOAT, pixels.data());
		glBindFramebuffer(GL_READ_FRAMEBUFFER, frame.framebuffer);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBlitFramebuffer(0, 0, image_width, image_height, 0, 0, image_width, image_height,	GL_COLOR_BUFFER_BIT, GL_NEAREST);

		glfwSwapBuffers(window.window);
		glfwPollEvents();
	}
	glfwTerminate();
}
