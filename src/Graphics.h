#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Window.h"
#include "Utils/Frame.h"

Window createWindow(unsigned int dx, unsigned int dy);

Frame createTexture();
