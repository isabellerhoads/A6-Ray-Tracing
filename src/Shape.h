#pragma once
#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <vector>
#include <memory>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/fwd.hpp>

#include "Hit.h"
#include "Ray.h"
#include "Material.h"

class Shape
{
public:

	virtual std::shared_ptr<Hit> Intersect(std::shared_ptr<Ray> ray) { return NULL; }

};


/* Sphere: subclass of Shape */
class Sphere : public Shape
{
public:

	Sphere(glm::vec3 pos, glm::vec3 sc, float r) : position(pos), scale(sc), radius(r) {}

	void setMat(Material m)
	{
		mat = m;
	}

	std::shared_ptr<Hit> Intersect(std::shared_ptr<Ray> ray)
	{
		glm::vec3 p = ray->getPosition(), v = ray->getDirection();
		// v.z = -v.z;

		glm::vec3 pc = p - position;
		float a = dot(v, v);
		float b = 2 * dot(v, pc);
		float c = dot(pc, pc) - pow(radius, 2);
		float d = pow(b, 2) - (4 * a * c);

		if (d > 0) 
		{
			// std::cout << "intersect" << std::endl;
			float t1 = (-b + pow(d, 0.5)) / (2 * a);
			float t2 = (-b - pow(d, 0.5)) / (2 * a);
			glm::vec3 x1 = p + (t1 * v);
			glm::vec3 x2 = p + (t2 * v);
			glm::vec3 n1 = (x1 - position) / radius;
			glm::vec3 n2 = (x2 - position) / radius;

			std::shared_ptr<Hit> newHit1 = std::make_shared<Hit>(x1, n1, t1, this->mat);
			std::shared_ptr<Hit> newHit2 = std::make_shared<Hit>(x2, n2, t2, this->mat);

			if (t1 < t2) 
			{
				return newHit1;
			}
			return newHit2;

		}
		return NULL;
	}

private: 
	float radius;
	glm::vec3 position;
	glm::vec3 scale;
	Material mat;
};


/* Ellipsoid: subclass of Shape */ 
class Ellipsoid : public Shape
{
public:

	Ellipsoid(glm::vec3 pos, glm::vec3 sc, glm::mat4 e) : position(pos), scale(sc), ellipsoid_E(e) {}

	void setMat(Material m) { mat = m; }

	std::shared_ptr<Hit> Intersect(std::shared_ptr<Ray> ray) 
	{
		glm::vec3 p = ray->getPosition(), v = ray->getDirection();
	/*	v.z = -v.z;*/
		glm::mat4 E = inverse(ellipsoid_E);
		glm::vec3 p_prime = E * glm::vec4(p, 1.0f);
		glm::vec3 v_prime = E * glm::vec4(v, 0.0f);
		v_prime = normalize(v_prime);
		float a = dot(v_prime, v_prime);
		float b = 2 * dot(v_prime, p_prime);
		float c = dot(p_prime, p_prime) - 1;
		float d = pow(b, 2) - (4 * a * c);

		if (d > 0) 
		{
			float t1 = (-b + pow(d, 0.5)) / (2 * a);
			float t2 = (-b - pow(d, 0.5)) / (2 * a);
			glm::vec3 x1 = p_prime + (t1 * v_prime);
			glm::vec3 x2 = p_prime + (t2 * v_prime);
			glm::vec3 n1 = normalize(transpose(E) * glm::vec4(x1, 0.0f));
			glm::vec3 n2 = normalize(transpose(E) * glm::vec4(x2, 0.0f));
			x1 = ellipsoid_E * glm::vec4(x1, 1.0f);
			x2 = ellipsoid_E * glm::vec4(x2, 1.0f);
			t1 = length(x1 - p);
			t2 = length(x2 - p);

			if (dot(v, x1 - p) < 0) 
			{
				t1 = -t1;
			}
			if (dot(v, x2 - p) < 0) 
			{
				t2 = -t2;
			}

			std::shared_ptr<Hit> newHit1 = std::make_shared<Hit>(x1, n1, t1, this->mat);
			std::shared_ptr<Hit> newHit2 = std::make_shared<Hit>(x2, n2, t2, this->mat);

			if (t1 < t2)
			{
				return newHit1;
			}
			return newHit2;
		}
		return NULL;
	}

private:
	glm::mat4 ellipsoid_E;
	glm::vec3 position;
	glm::vec3 scale;
	Material mat;
};

/* Plane: subclass of Shape */
class Plane : public Shape
{
public:

	Plane(glm::vec3 pos, glm::vec3 nor) : position(pos), normal(nor) {}

	void setMat(Material m) { mat = m; }

	std::shared_ptr<Hit> Intersect(std::shared_ptr<Ray> ray) 
	{
		glm::vec3 p = ray->getPosition(), v = ray->getDirection();
		glm::vec3 c = position;
		glm::vec3 n = normal;
		//std::cout << dot(n, v) << std::endl;
		float t = (dot(n, (c - p))) / dot(n, v);
		glm::vec3 x = p + (t * v);
		std::shared_ptr<Hit> newHit = std::make_shared<Hit>(x, n, t, this->mat);
		
		return newHit;
	}

private:
	glm::vec3 position;
	glm::vec3 normal;
	Material mat;
};

#endif