#pragma once

#include "Mat.h"
#include "Sphere.h"
#include <vector>

struct Scene{
	std::vector<Sphere> spheres;
	std::vector<Mat> materialList;
};
