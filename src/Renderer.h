#pragma once

#include "Scene.h"
#include "glm/glm.hpp"
#include "Ray.h"
#include "glm/common.hpp"
#include "glm/geometric.hpp"

glm::vec4 processPixel(Ray ray, Scene& scene);
