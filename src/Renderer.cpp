#include "Renderer.h"
#define RAND(X) static_cast <float> (rand()) / static_cast <float> (RAND_MAX)

HitData Renderer::trace(Ray& ray){
	float closestT = FLT_MAX;
	int closestSphereIndex = -1;

	for(int i = 0; i < scene->objects.size(); i++){
		float t = scene->objects[i]->intersect(ray);
		if(t < closestT && t > 0){
			closestT = t;
			closestSphereIndex = i;
		}
	}
	if(closestSphereIndex < 0)
		return miss();
	return scene->objects[closestSphereIndex]->hit(ray, closestT, closestSphereIndex);
}

HitData Renderer::miss(){
	HitData data;
	data.objectIndex = -1;
	return data;
}
glm::vec4 Renderer::processPixel(Ray ray){
	glm::vec4 finalColor(0.0f);
	int bounces = 5;
	glm::vec3 light = glm::normalize(glm::vec3(-1, -1, -1));
	glm::vec4 skyBox = {0.6f, 0.6f, 0.9f, 1.0f};

	for(int i = 0; i < bounces; i++){
		HitData data = trace(ray);
		if(data.objectIndex < 0){
			finalColor += skyBox * (float)std::pow(0.5, i);
			break;
		}
		else{
			float d = glm::max(glm::dot(data.normal, -light), 0.0f);
			finalColor += glm::vec4(d * scene->materialList[scene->objects[data.objectIndex]->matIndex].Albedo, 1.0f) * (float)std::pow(0.5, i);
			ray.origin = data.position + data.normal * 0.001f;
			ray.rayDirection = glm::reflect(ray.rayDirection, data.normal + (scene->materialList[scene->objects[data.objectIndex]->matIndex].roughness * glm::vec3(RAND(1.0f)-0.5f, RAND(1.0f)-0.5f, RAND(1.0f)-0.5f)));
		}
	}

	return finalColor;	
}
