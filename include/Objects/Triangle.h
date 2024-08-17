#pragma once
#include "Object.h"

class Triangle : public Object{
    public:
		Triangle(glm::vec3 t_v1, glm::vec3 t_v2, glm::vec3 t_v3, int matI){
			v1 = t_v1;
            v2 = t_v2;
            v3 = t_v3;
            matIndex = matI;
		}
        glm::vec3 v1;
        glm::vec3 v2;
        glm::vec3 v3;
		float intersect(Ray& ray);
		HitData hit(Ray& ray, float hitDistance, int objectIndex);
};