//CXX STL includes
#include <iostream>
#include <vector>

/*
GLAD : OpenGL Wrapper, included first per documentation
GLFW : OpenGL Window wrapper and OpenGL Context Initialization
GLM  : All Vector and Matrix mathamatics handled to avoid proprietary classes
*/

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

/*
Graphics.h : Creation of the Window and the creation and initialization of the Texture.
Renderer.h : Main Pixel Processing load and Trace/miss implementations for the Object System.
Blit.h     : OpenGL texture pipeline and bliting the framebuffer.
Camera.h   : generation of ray directions before the main Render loop.
*/

/*
Utils/Frame.h : Wrapper struct for the texture and the framebuffer.
Utils/Ray.h   : Wrapper struct for holding the components of a ray -> Direction and origin.
Utils/Scene.h : Collection of all the object child instances, materials and light direction.
*/

/*
Objects/Sphere.h : Sphere Child class for Object system : Quadratic formula to detect ray intersection and returns HitData for Ray Tracing.
Objects/Plane.h  : Plane Child class for Object system  : Plane ray intersection and returns HitData for Ray Tracing. 
*/

#include "Graphics.h"
#include "Renderer.h"
#include "Blit.h"
#include "Camera.h"
#include "Utils/Frame.h"
#include "Utils/Ray.h"
#include "Utils/Scene.h"
#include "Objects/Sphere.h"
#include "Objects/Plane.h"