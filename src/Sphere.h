#pragma once

#include "Mat.h"
#include "glm/glm.hpp"

struct Sphere{
	glm::vec3 position{0, 0, 0};
	float radius = 1.0f;
	int matIndex;
};
