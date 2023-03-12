#pragma once

#include "Mat.h"
#include "Object.h"
#include "Sphere.h"
#include <vector>
#include <memory>

struct Scene{
	std::vector<std::unique_ptr<Object>> objects;
	std::vector<Mat> materialList;
};
