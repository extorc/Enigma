#pragma once
#include "Ray.h"

class Object{
	public:
		virtual float intersect(Ray& ray) = 0;
};
