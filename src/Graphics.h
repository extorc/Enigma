#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Window.h"

Window createWindow(){
	GLFWwindow* window;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwInit();

	window = glfwCreateWindow(500, 500, "Enigma", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	return Window{window, 500, 500};
}
