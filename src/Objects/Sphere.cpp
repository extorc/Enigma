#include "Sphere.h"

float Sphere::intersect(Ray& ray){

	//A is direction.direction which is 1 for normalised vectors
	float halfB = glm::dot(ray.rayDirection, ray.origin - position);
	float c = glm::dot(ray.origin - position, ray.origin - position) - radius * radius;

	/*Quadratic equation of the sphere is foudn to be

		Ax^2 + Bx^2T^2 + 2AxBxt + g^2 - 2gAx - 2gBxt +
		Ay^2 + By^2T^2 + 2AyByt + h^2 - 2hAy - 2hByt + 
		Az^2 + Bz^2T^2 + 2AzBzt + i^2 - 2zAz - 2iBzt - Radius ^ 2

		^        ^         ^         ^         ^       ^ 
		|        |         |         |         |       | 
		const	  T^2 term    T term    const     T term   const

*/ 

	float discriminant = (halfB * halfB) - c;
	//-b +/- sqrt(b^2-4c) /2 = -halfB +/- sqrt(halfB^2 - c) 
	if(discriminant >= 0){
		float quadSol1 = -halfB - std::sqrt(discriminant);
		float quadSol2 = -halfB + std::sqrt(discriminant);

		if(quadSol1 < 0 && quadSol2 < 0)
			return -1;
		else if(quadSol1 < 0)
			return quadSol2;
		else 
			return quadSol1;
	}

	return -1;
}
HitData Sphere::hit(Ray& ray, float hitDistance, int objectIndex){
	HitData data;
	data.hitDistance = hitDistance;
	data.objectIndex = objectIndex;
	data.position = hitDistance * ray.rayDirection + ray.origin;
	data.normal = glm::normalize(data.position - position);
	return data;
}
