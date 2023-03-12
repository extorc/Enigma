#pragma once

#include "Mat.h"
#include "Ray.h"
#include "glm/glm.hpp"
#include "Object.h"

class Sphere : public Object{
	public:
		Sphere(glm::vec3 pos, float rad, int matI){
			position = pos;
			radius = rad;
			matIndex = matI;
		}
		float radius = 1.0f;
		float intersect(Ray& ray);
};
