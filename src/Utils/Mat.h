#pragma once
#include "glm/glm.hpp"

typedef struct{
	float roughness;
	float specular;
	glm::vec3 Albedo{1, 0, 1};
}Mat;
