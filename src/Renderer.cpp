#include "Renderer.h"
#include <climits>

HitData Renderer::trace(Ray& ray){
	float closestT = FLT_MAX;
	int closestSphereIndex = -1;

	for(int i = 0; i < scene.spheres.size(); i++){
		Sphere sphere = scene.spheres[i];
		//A is direction.direction which is 1 for normalised vectors
		float halfB = glm::dot(ray.rayDirection, ray.origin - sphere.position);
		float c = glm::dot(ray.origin - sphere.position, ray.origin - sphere.position) - sphere.radius * sphere.radius;

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

			float t;
			if(quadSol1 < 0 && quadSol2 < 0)
				continue;
			else if(quadSol1 < 0)
				t = quadSol2;
			else 
				t = quadSol1;
			if(t < closestT){
				closestT = t;
				closestSphereIndex = i;
			}
		}
	}
	if(closestSphereIndex < 0)
		return miss();
	return hit(ray, closestT, closestSphereIndex);
}

HitData Renderer::hit(Ray& ray, float hitDistance, int objectIndex){
	HitData data;
	data.hitDistance = hitDistance;
	data.objectIndex = objectIndex;
	data.position = hitDistance * ray.rayDirection + ray.origin;
	data.normal = glm::normalize(data.position - scene.spheres[objectIndex].position);
	return data;
}
HitData Renderer::miss(){
	HitData data;
	data.objectIndex = -1;
	return data;
}
glm::vec4 Renderer::processPixel(Ray& ray){
	HitData data = trace(ray);
	glm::vec3 light = glm::normalize(glm::vec3(-1, -1, -1));

	if(data.objectIndex < 0)
		return glm::vec4(0.0f);

	float d = glm::max(glm::dot(data.normal, -light), 0.0f);
	return glm::vec4(d * scene.spheres[data.objectIndex].Albedo, 1.0f);	
}
