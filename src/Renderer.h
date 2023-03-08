#pragma once

#include "glm/glm.hpp"
#include "Ray.h"
#include "glm/common.hpp"
#include "glm/geometric.hpp"

glm::vec4 processPixel(Ray ray, glm::vec3 objectPosition, glm::vec3 objectColor);
