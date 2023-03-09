#pragma once

#include "glm/glm.hpp"

struct Sphere{
	glm::vec3 position{0, 0, 0};
	float radius = 1.0f;
	glm::vec3 Albedo{1, 0, 1};
};
