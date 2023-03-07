#include "Camera.h"

void Camera::calculateRayDirections(){
	for(int j = 0; j < v; j++){
		for(int i = 0; i < u; i++){
			glm::vec2 ndc((float)i/(float)u, (float)j/(float)v);
			glm::vec2 screen = ndc * 2.0f - 1.0f; 
			glm::vec4 target = glm::vec4(screen, 2.5f, 1);
			rayDirections.push_back(glm::vec3(getInverseMatrix() * glm::vec4(glm::normalize(glm::vec3(target) / target.w), 0)));
		}
	}
}

glm::mat4 Camera::getInverseMatrix(){
	return glm::inverse(glm::lookAt(cameraPosition, cameraPosition + forwardDirection, glm::vec3(0, -1, 0)));
}
