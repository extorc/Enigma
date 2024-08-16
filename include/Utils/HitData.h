#pragma once

#include "glm/glm.hpp"

typedef struct{
	float hitDistance;
	glm::vec3 position;
	glm::vec3 normal;
	float objectIndex;
}HitData;
