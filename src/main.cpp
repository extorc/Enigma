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

glm::vec4 processPixel(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::vec3 objectPosition){
	float a = glm::dot(rayDirection, rayDirection);
	float b = 2 * glm::dot(rayDirection, rayOrigin - objectPosition);
	float c = glm::dot(rayOrigin, rayOrigin) - 81.0f - 2 * glm::dot(rayOrigin, objectPosition) + glm::dot(objectPosition, objectPosition);

	/*Quadratic equation of the sphere is foudn to be

		Ax^2 + Bx^2T^2 + 2AxBxt + g^2 - 2gAx - 2gBxt +
		Ay^2 + By^2T^2 + 2AyByt + h^2 - 2hAy - 2hByt + 
		Az^2 + Bz^2T^2 + 2AzBzt + i^2 - 2zAz - 2iBzt - Radius ^ 2
		  
     ^        ^         ^         ^         ^       ^ 
		 |        |         |         |         |       | 
	const	  T^2 term    T term    const     T term   const
                                                   
		*/                                             
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
	glm::vec3 sphere(0.0f, 0.0f, 9.0f);

	for(int j = 0; j < image_height; j++){
		for(int i = 0; i < image_width; i++){
			glm::vec3 pixel(i-250, j-250, 129.4f); //Z coord is foud by hit and trial to be good enough for zooming in on the sphere at this potiion. It only affects field of view
			glm::vec3 ray = pixel - origin;
			pixels.push_back(processPixel(origin, glm::normalize(ray), sphere));
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
