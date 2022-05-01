#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/fwd.hpp>

class Light
{
public:
	Light(glm::vec3 pos, glm::vec3 col, float inten) 
	{
		position = pos;
		color = col;
		intensity = inten;
	}

	glm::vec3 getColor() { return color; }
	glm::vec3 getPosition() { return position; }
	float getIntensity() { return intensity; }

	void setPosition(glm::vec3 worldPos) 
	{
		position = worldPos;
	}

private:
	glm::vec3 position;
	glm::vec3 color;
	float intensity;
};

#endif