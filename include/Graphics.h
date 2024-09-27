#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Window.h"
#include <iostream>

Window createWindow(unsigned int dx, unsigned int dy);
GLuint createShader(int type, const char* source);
void checkShaderCompilation(unsigned int shader, int type);