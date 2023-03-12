#pragma once

#include "Scene.h"
#include "glm/glm.hpp"
#include "Ray.h"
#include "glm/common.hpp"
#include "glm/geometric.hpp"
#include "Camera.h"
#include "HitData.h"

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
