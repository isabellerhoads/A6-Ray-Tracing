#pragma  once
#ifndef RAY_H
#define RAY_H

#include <vector>
#include <iostream>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/fwd.hpp>

class Ray
{
public:

	Ray(glm::vec3 p, glm::vec3 v) : position(p), direction(v) {}
	void printDirection() { std::cout << direction.x << ", " << direction.y << ", " << direction.z << std::endl; }
	glm::vec3 getPosition() { return position; }
	glm::vec3 getDirection() { return direction; }

private:
	glm::vec3 position;
	glm::vec3 direction;
};

#endif