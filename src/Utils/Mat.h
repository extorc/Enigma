#pragma once
#include "glm/glm.hpp"

struct Mat{
	float roughness;
	float specular;
	glm::vec3 Albedo{1, 0, 1};
};
