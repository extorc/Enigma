#pragma once

#include "Mat.h"
#include "Objects/Object.h"
#include "Objects/Sphere.h"
#include <vector>
#include <memory>

struct Scene{
	std::vector<std::unique_ptr<Object>> objects;
	std::vector<Mat> materialList;
};
