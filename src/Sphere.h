#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

#include <string>
#include <vector>
#include <memory>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/fwd.hpp>

#include "Hit.h"
#include "Ray.h"
#include "Material.h"

class Sphere : public Shape
{


public:

	Sphere(glm::vec3 pos, glm::vec3 sc) : position(pos), scale(sc), radius(1.0f) {}

	void setMat(Material m)
	{
		mat = m;
	}
	void printHits()
	{
		std::cout << hits.size() << std::endl;
		for (int i = 0; i < hits.size(); i++) {
			hits.at(i).printHit();
		}
	}

	void setRadius(float r) { radius = r; }

	float Intersect(std::shared_ptr<Ray> ray, Hit& hit)
	{
		glm::vec3 p = ray->getPosition(), v = ray->getDirection();
		glm::vec3 pc = p - position;
		float a = dot(v, v);
		float b = 2 * dot(v, pc);
		float c = dot(pc, pc) - pow(radius, 2);
		float d = pow(b, 2) - (4 * a * c);
		if (d > 0) {
			// std::cout << "two hits on sphere" << std::endl;
			float t1 = (-b + pow(d, 0.5)) / (2 * a);
			float t2 = (-b - pow(d, 0.5)) / (2 * a);
			glm::vec3 x1 = p + (t1 * v);
			glm::vec3 x2 = p + (t2 * v);
			glm::vec3 n1 = (x1 - position) / radius;
			glm::vec3 n2 = (x2 - position) / radius;
			Hit newHit1(x1, n1, t1, this->mat);
			Hit newHit2(x2, n2, t2, this->mat);
			if (t1 < t2)
			{
				hit = newHit1;
				return t1;
			}
			hit = newHit2;
			return t2;
		}
		return INFINITY;
	}

	float radius;
	glm::vec3 position;
	glm::vec3 scale;
	Material mat;
	std::vector<Hit> hits;
};

#endif