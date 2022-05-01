#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/fwd.hpp>

#include <memory>
#include <vector>

#include "Camera.h"
#include "Ray.h"
#include "Scene.h"

using namespace std;

void Camera::generateRays(glm::vec3 plane, std::shared_ptr<Image> image, std::shared_ptr<Scene> scene, bool reflection)
{
	float height = glm::tan(fov / 2) /** (this->position.z - plane.z)*/ * 2;
	float pixel = height / this->size;
	glm::vec3 color;
	float center = pixel / 2;

	for (int i = 0; i < size; i++) 
	{
		for (int j = 0; j < size; j++) 
		{
			float x = (center + i * pixel) - (height / 2);
			float y = (center + j * pixel) - (height / 2);
			glm::vec3 pix = glm::vec3(x, y, plane.z);
			glm::vec3 direction = pix - this->position;
			auto ray = make_shared<Ray>(this->position, normalize(direction));
			color = scene->computeRayColor(ray, 0, INFINITY, this->position);

			image->setPixel(size - 1 - i, size - 1 - j, color.x*255, color.y*255, color.z*255);

			//x += pixel;
		}
		//y -= pixel;
	}
}