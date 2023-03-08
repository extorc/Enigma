#include "Renderer.h"

glm::vec4 processPixel(Ray ray, glm::vec3 objectPosition, glm::vec3 objectColor){

	glm::vec3 light = glm::normalize(glm::vec3(-1, -1, -1));

	float a = glm::dot(ray.rayDirection, ray.rayDirection);
	float b = 2 * glm::dot(ray.rayDirection, ray.origin - objectPosition);
	float c = glm::dot(ray.origin, ray.origin) 
					- 1.0f 
					- 2 * glm::dot(ray.origin, objectPosition) 
					+ glm::dot(objectPosition, objectPosition);

	/*Quadratic equation of the sphere is foudn to be

		Ax^2 + Bx^2T^2 + 2AxBxt + g^2 - 2gAx - 2gBxt +
		Ay^2 + By^2T^2 + 2AyByt + h^2 - 2hAy - 2hByt + 
		Az^2 + Bz^2T^2 + 2AzBzt + i^2 - 2zAz - 2iBzt - Radius ^ 2
		  
     ^        ^         ^         ^         ^       ^ 
		 |        |         |         |         |       | 
	const	  T^2 term    T term    const     T term   const
                                                   
		*/                                             
	float discriminant = (b * b) - 4 * a * c;

	if(discriminant >= 0){
		float quadSol1 = ((b * -1) - std::sqrt(discriminant))/(2 * a);
		float quadSol2 = ((b * -1) + std::sqrt(discriminant))/(2 * a);
		
		float t;
		if(quadSol1 < 0)
			t = quadSol2;
		else
			t = quadSol1;

		glm::vec3 intercept = t * ray.rayDirection + ray.origin;
		glm::vec3 normal = glm::normalize(intercept - objectPosition);
		
		float d = glm::max(glm::dot(normal, -light), 0.0f);
		return glm::vec4(d * objectColor, 1.0f);
	}
	else
		return glm::vec4(0.0f);
}
