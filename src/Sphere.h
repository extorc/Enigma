#pragma once

#include "Mat.h"
#include "Ray.h"
#include "glm/glm.hpp"
#include "Object.h"

class Sphere : public Object{
	public:
		glm::vec3 position{0, 0, 0};
		float radius = 1.0f;
		int matIndex;
		float intersect(Ray& ray);
};
