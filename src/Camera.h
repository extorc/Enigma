#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

class Camera{
	public:
		Camera(glm::vec3 origin, int image_width, int image_height):cameraPosition(origin), u(image_width), v(image_height){}
		int u;
		int v;
		glm::vec3 cameraPosition;
		glm::vec3 forwardDirection = glm::vec3(0, 0, -1);
		glm::vec3 upDirection = glm::vec3(0, -1, 0);
		std::vector<glm::vec3> rayDirections;

		void calculateRayDirections();
		glm::mat4 getInverseMatrix();
		void rotateCamera(float pitch, float yaw);
		void translateCamera(glm::vec3 t);
};
