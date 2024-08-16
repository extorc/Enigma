#include "Objects/Plane.h"

float Plane::intersect(Ray& ray){
	float t = glm::dot(planePoint - ray.origin, planeNormal)/glm::dot(ray.rayDirection, planeNormal);
	if(t < 0)
		return -1;
	return t;
}

HitData Plane::hit(Ray& ray, float hitDistance, int objectIndex){
	HitData data;
	data.hitDistance = hitDistance;
	data.objectIndex = objectIndex;
	data.position = hitDistance * ray.rayDirection + ray.origin;
	data.normal = planeNormal;
	return data;
}
