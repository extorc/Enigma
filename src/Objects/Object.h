#pragma once
#include "Utils/HitData.h"
#include "Utils/Ray.h"

class Object{
	public:
		virtual float intersect(Ray& ray) = 0;
		virtual HitData hit(Ray& ray, float hitDistance, int objectIndex) = 0;
		glm::vec3 position{0, 0, 0};
		int matIndex;
};
