#pragma once

#include "Utils/Scene.h"
#include "Utils/HitData.h"
#include "Utils/Ray.h"
#include "glm/glm.hpp"
#include "glm/common.hpp"
#include "glm/geometric.hpp"
#include "Camera.h"
#include <climits>
#include <cmath>
#include <iostream>

class Renderer{
	public:
		Renderer(Camera camera, Scene* scene):camera(camera), scene(scene){}
		glm::vec4 processPixel(Ray ray);
	private:
		HitData trace(Ray& ray);
		HitData miss();

		Camera camera;
		Scene* scene;
};
