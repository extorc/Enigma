#include <iostream>
#include "Graphics.h"
#include "Vec3.h"
#include <fstream>
#include <cstdio>
#include <ostream>
#include <string>
#include "glad/glad.h"
#include "GLFW/glfw3.h"


std::ofstream file("../output.ppm");

void write(Vec3f color){
	file<<std::to_string(color.x) + " " + std::to_string(color.y) + " " + std::to_string(color.z) + "\n" ;
}

int main(){
	GLFWwindow* window;
	createWindow(window);

	while(!glfwWindowShouldClose(window)){  //segfault
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	int image_height = 500;
	int image_width = 500;

	file<<"P3\n";
	file<<"500 500\n";
	file<<"255\n";

	Vec3f origin(0.0f, 0.0f, -5.4f); 

	for(int j = 0; j < image_height; j++){
		for(int i = 0; i < image_width; i++){
			Vec3f pixel(i-250, 250-j, 0);

			Vec3f ray = pixel - origin;
			
			float a = Vec3f::dot(ray, ray);
			float b = 2 * Vec3f::dot(ray, origin);
			float c = Vec3f::dot(origin, origin) - 29.0f;
			
			float discriminant = (b * b) - 4 * a * c;

			if(discriminant >= 0){
				write(Vec3f(255, 255, 255));
			}
			else{
				write(Vec3f(0, 0, 0));
			}
		}
	}

	glfwTerminate();
	file.close();
}
