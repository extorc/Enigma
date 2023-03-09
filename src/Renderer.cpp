#include "Renderer.h"
#include <climits>

glm::vec4 processPixel(Ray& ray, Scene& scene){

	glm::vec3 light = glm::normalize(glm::vec3(-1, -1, -1));
	float closestT = FLT_MAX;
	int closestSphereIndex = INT_MAX;

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
			if(quadSol1 < 0)
				t = quadSol2;
			else
				t = quadSol1;
			if(t < closestT){
				closestT = t;
				closestSphereIndex = i;
			}
		}
	}
	if(closestSphereIndex == INT_MAX)
		return glm::vec4(0.0f);
	else{
		glm::vec3 intercept = closestT * ray.rayDirection + ray.origin;
		glm::vec3 normal = glm::normalize(intercept -scene.spheres[closestSphereIndex].position);

		float d = glm::max(glm::dot(normal, -light), 0.0f);
		return glm::vec4(d * scene.spheres[closestSphereIndex].Albedo, 1.0f);	
	}
}
