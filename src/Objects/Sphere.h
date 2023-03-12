#pragma once

#include "Utils/Mat.h"
#include "Utils/Ray.h"
#include "glm/glm.hpp"
#include "Object.h"
#include "Utils/HitData.h"

class Sphere : public Object{
	public:
		Sphere(glm::vec3 pos, float rad, int matI){
			position = pos;
			radius = rad;
			matIndex = matI;
		}
		float radius = 1.0f;
		float intersect(Ray& ray);
		HitData hit(Ray& ray, float hitDistance, int objectIndex);
};
