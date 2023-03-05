#pragma once
#include "glm/fwd.hpp"
#include <glad/glad.h>
#include <glad/glad.h>
#include <vector>

struct Frame{
	GLuint texture;
	GLuint framebuffer;
};

void blitFrame(Frame frame, int u, int v, std::vector<glm::vec4> pixels);
