#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Light.h"
#include <memory>
#include <vector>

class Material
{
public:
	Material() {}
	Material(glm::vec3 kd, glm::vec3 ks, glm::vec3 ka, float s) : ka(ka), kd(kd), ks(ks), s(s) {}
	glm::vec3 get_ambient();
	glm::vec3 get_diffuse();
	glm::vec3 get_specular();
	float get_shininess();
	// glm::vec3 computeBP(std::vector<std::shared_ptr<Light>> lights, glm::vec3 position, glm::vec3 normal, glm::vec3 camPos, Scene scene);

private:
	glm::vec3 ka;
	glm::vec3 kd;
	glm::vec3 ks;
	float s;
};

#endif