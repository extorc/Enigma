#pragma once

#include "Mat.h"
#include "Objects/Object.h"
#include "Objects/Sphere.h"
#include "glm/ext/quaternion_geometric.hpp"
#include <vector>
#include <memory>

struct Scene{
	std::vector<std::unique_ptr<Object>> objects;
	std::vector<Mat> materialList;
	glm::vec3 light = glm::normalize(glm::vec3(-1, -1, -1));
};
