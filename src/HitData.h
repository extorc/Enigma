#pragma once

#include "glm/glm.hpp"

struct HitData{
	float hitDistance;
	glm::vec3 position;
	glm::vec3 normal;
	float objectIndex;
};
