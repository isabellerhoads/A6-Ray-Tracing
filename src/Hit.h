#pragma once
#ifndef HIT_H
#define HIT_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/fwd.hpp>

#include "Material.h"

class Hit
{
public:
	Hit() : x(0), n(0), t(0), mat(Material()) {}
	Hit(const glm::vec3& x, const glm::vec3& n, float t, Material m) { this->x = x; this->n = n; this->t = t; this->mat = m; }
	void printHit() 
	{
		std::cout << x.x << ", " << x.y << ", " << x.z << std::endl;
	}
	float getT() { return t; }
	Material getMat() { return mat; }
	glm::vec3 getPosition() { return x; }
	glm::vec3 getNormal() { return n; }

	glm::vec3 x; // position
	glm::vec3 n; // normal
	float t; // distance
	Material mat;
};

#endif