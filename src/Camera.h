#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/fwd.hpp>

#include <memory>
#include <vector>

#include "Ray.h"
#include "Scene.h"
#include "Image.h"

class Camera
{
public:

	Camera(glm::vec3 p, float f, float s) : position(p), fov(f), size(s) {}
	void generateRays(glm::vec3 plane, std::shared_ptr<Image> image, std::shared_ptr<Scene> scene, bool reflection);

private:
	glm::vec3 position;
	float aspect = 1.0;
	float fov;
	float size;
};

#endif