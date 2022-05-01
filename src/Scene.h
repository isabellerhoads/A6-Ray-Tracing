#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>
#include <memory>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/fwd.hpp>

#include "Light.h"
#include "Hit.h"
#include "Ray.h"
#include "Shape.h"

class Shape;

class Scene
{
public:
	Scene() : sceneNumber(0) {}
	virtual ~Scene();
	void addShape(std::shared_ptr<Shape> shape);
	void addLight(std::shared_ptr<Light> light);
	void setNumber(int num);
	std::shared_ptr<Hit> hit(std::shared_ptr<Ray> ray, float t0, float t1);
	glm::vec3 computeRayColor(std::shared_ptr<Ray> ray, float t0, float t1, glm::vec3 camPos);
	glm::vec3 computeBP(std::shared_ptr<Hit> ht, glm::vec3 camPos);

private:
	std::vector<std::shared_ptr<Shape>> shapes;
	std::vector<std::shared_ptr<Light>> lights;
	int sceneNumber;
};

#endif