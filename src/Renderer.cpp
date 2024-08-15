#include "Renderer.h"
#include "glm/ext/quaternion_geometric.hpp"
#include <cmath>
#define RAND(X) static_cast <float> (rand()) / static_cast <float> (RAND_MAX)
#define ROUGH_FUNC(r) 32/((r + 1) * ((2.1f * r * 10/11) + 1))

HitData Renderer::trace(Ray& ray){
	float closestT = FLT_MAX;                                                                        //Keeping track of Closest distance of collision and the object occupied at that distance
	int closestObjectIndex = -1;

	for(int i = 0; i < scene->objects.size(); i++){
		float t = scene->objects[i]->intersect(ray);                                                   //Looping through all the objects in the scene and running their respective intersect functions
		if(t < closestT && t > 0){
			closestT = t;                                                                                //Updating the closest distance and object in case we have a nearer candidate
			closestObjectIndex = i;
		}
	}
	if(closestObjectIndex < 0)
		return miss();                                                                                 //If no close object was detected, run the global miss function
	return scene->objects[closestObjectIndex]->hit(ray, closestT, closestObjectIndex);               //Otherwise return the data about this collision
}

HitData Renderer::miss(){
	HitData data;
	data.objectIndex = -1;
	return data;
}

glm::vec4 Renderer::processPixel(Ray& ray){
	glm::vec4 finalColor(0.0f);
	int bounces = 5;
	glm::vec4 skyBox = {0.6f, 0.6f, 0.9f, 1.0f};

	for(int i = 0; i < bounces; i++){
		HitData data = trace(ray);
		if(data.objectIndex < 0){                                                                      //If we didnt hit anything during the bounce race, just append the sky color
			finalColor += skyBox * (float)std::pow(0.5, i);
			break;
		}
		else{

			/*
			 Firstly, calculate the light intensity at the point by comparing normal orientation with light direction
			 Then, calculate the specular intensity, which depends on the comparison between reflected ray and light ray. ALso controll fall-off based on roughness function 32/(x+1)(2.1x/11 + 1) 
			 Update color based on object color, light intensity and specular intensity calculated above
			 Correct for self collision in preparation for bounce
			 Update ray direction by reflecting the ray at collision site + randomizing normal to introduce roughness before re-calling trace
			 */

			Mat objectMat = scene->materialList[scene->objects[data.objectIndex]->matIndex];
			float d = glm::max(glm::dot(data.normal, -scene->light), 0.0f);
			glm::vec3 diffuseLighted = d * objectMat.Albedo;

			float s = std::pow(glm::max(glm::min(glm::dot(glm::reflect(ray.rayDirection, data.normal), -scene->light), 1.0f), 0.0f), ROUGH_FUNC(objectMat.roughness));
			glm::vec3 specularLighted = glm::vec3(1);
			
			finalColor += glm::vec4(diffuseLighted + (1 - objectMat.roughness) * objectMat.specular  * specularLighted * s, 1.0f) * (float)std::pow(0.5, i);
			
			ray.origin = data.position + data.normal * 0.001f;
			ray.rayDirection = glm::reflect(ray.rayDirection, data.normal + objectMat.roughness * glm::vec3(RAND(1.0f)-0.5f, RAND(1.0f)-0.5f, RAND(1.0f)-0.5f));
		}
	}

	return finalColor;	
}
