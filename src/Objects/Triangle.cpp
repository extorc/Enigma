#include "Objects/Triangle.h"

/*
The implementation for the Triangle Ray intersection is done using the Möller–Trumbore intersection algorithm
Read more at https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm

This involves representing any point within the plane of the triangle one the basis of its Barycentric coordinates.

Barrycentric coordinates are independant of the position and orientation of the object.
These coordinates of the supposed intersection point are equated to the ray equation and we solve for u v and t.
If u and v are within the respectable bounds, we solve for t and return.
*/

float Triangle::intersect(Ray& ray){
    glm::vec3 e1 = v2 - v1;
    glm::vec3 e2 = v3 - v1;

    int a = glm::dot(glm::cross(e2, e1), ray.rayDirection);
    if(a < .001f && a > -.001f) return -1;
    // Check if the ray is parellel to the triangle, if yes, exit

    float inv_a = 1.0/a;
    glm::vec3 s = ray.origin - v1;

    float u = inv_a * glm::dot(ray.rayDirection, glm::cross(s, e2));
    if(u < 0 || u > 1) return -1;

    float v = inv_a * glm::dot(ray.rayDirection, glm::cross(e1, s));
    if(v < 0 || u + v > 1) return -1;

    float t  = inv_a * glm::dot(s, glm::cross(e1, e2));
    if(t > 0.001f){
        return t;
    } else return -1;
}

HitData Triangle::hit(Ray& ray, float hitDistance, int objectIndex){
    HitData data;
    data.hitDistance = hitDistance;
    data.objectIndex = objectIndex;
    data.position = hitDistance * ray.rayDirection + ray.origin;
    data.normal = glm::normalize(glm::cross(v2-v1, v3-v1));
    return data;
}