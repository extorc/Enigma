#pragma once

#include "Object.h"

class Plane : public Object{
	public:
		Plane(glm::vec3 pos, glm::vec3 planeP, glm::vec3 planeN, int matI){
			position = pos;
			matIndex = matI;
			planePoint = planeP;
			planeNormal = planeN;
		}
		float intersect(Ray& ray) override;
		HitData hit(Ray& ray, float hitDistance, int objectIndex) override ;
		glm::vec3 planePoint;
		glm::vec3 planeNormal;
};
