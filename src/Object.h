#pragma once
#include "Ray.h"

class Object{
	public:
		virtual float intersect(Ray& ray) = 0;
		glm::vec3 position{0, 0, 0};
		int matIndex;
};
