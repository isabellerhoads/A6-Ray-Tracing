#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/fwd.hpp>

#include <memory>
#include <vector>
#include <limits>

#include "Scene.h"
#include "Light.h"
#include "Shape.h"
#include "Ray.h"
#include "Hit.h"

using namespace std;

Scene::~Scene()
{

}

void Scene::addShape(shared_ptr<Shape> shape)
{
	shapes.push_back(shape);
}

void Scene::addLight(shared_ptr<Light> light)
{
	lights.push_back(light);
}

void Scene::setNumber(int num)
{
	sceneNumber = num;
}

std::shared_ptr<Hit> Scene::hit(shared_ptr<Ray> ray, float t0, float t1)
{
	shared_ptr<Hit>  minHit = make_shared<Hit>();
	float min = t1;
	for (int i = 0; i < this->shapes.size(); i++)
	{
		shared_ptr<Hit> h = shapes.at(i)->Intersect(ray);
		if (h && h->getT() < min && h->getT() < t1 && h->getT() > t0)
		{
			minHit = h;
			min = h->getT();
		}
	}
	if (min < t1) 
	{
		return minHit;
	}
	return NULL;
}

glm::vec3 Scene::computeRayColor(shared_ptr<Ray> ray, float t0, float t1, glm::vec3 camPos)
{
	shared_ptr<Hit> h = make_shared<Hit>();
	h = hit(ray, t0, t1);

	if (h != NULL) 
	{
		/* if the ray hits a reflective object */
		if (h->getMat().get_diffuse() == glm::vec3(0.0f, 0.0f, 0.0f))
		{
			glm::vec3 I = ray->getDirection();
			glm::vec3 N = normalize(h->getNormal());
			glm::vec3 reflDir = reflect(I, N);
			shared_ptr<Ray> reflRay = make_shared<Ray>(h->getPosition() + (0.001f * reflDir), reflDir);

			return this->computeRayColor(reflRay, 0.01, 1000, h->getPosition());

			/* This is a single bounce without recursion */
			//shared_ptr<Hit> reflHit = make_shared<Hit>();
			//reflHit = hit(reflRay, 0.001, t1);

			//if (reflHit != NULL)
			//{
			//	return this->computeBP(reflHit, camPos);
			//}
		}
		/* if the ray hits a blinn-phong object */
		else
		{
			return this->computeBP(h, camPos);
		}
	}

	return glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::vec3 Scene::computeBP(std::shared_ptr<Hit> ht, glm::vec3 camPos)
{
	glm::vec3 n = normalize(ht->getNormal());

	glm::vec3 color = ht->getMat().get_ambient();

	for (auto light : lights)
	{
		bool shadow = false;
		float e = numeric_limits<float>::epsilon();

		glm::vec3 srayDir = normalize(light->getPosition() - ht->getPosition());
		auto sray = make_shared<Ray>(ht->getPosition() + (e * srayDir), srayDir);
		shared_ptr<Hit> shadHit = make_shared<Hit>();
		float tLight = length(light->getPosition() - ht->getPosition());

		shadHit = hit(sray, 0.0001f, tLight);

		if (shadHit != NULL)
		{
			float shadowDist = length(light->getPosition() - shadHit->getPosition());
			if (shadHit->getT() < tLight)
			{
				shadow = true;
			}
		}

		if (!shadow) 
		{
			glm::vec3 eye = camPos - ht->getPosition();
			glm::vec3 l = normalize(light->getPosition() - ht->getPosition());

			glm::vec3 h = normalize(l + normalize(eye));

			glm::vec3 cD = ht->getMat().get_diffuse() * max(0.0f, dot(l, n));
			glm::vec3 cS = ht->getMat().get_specular() * pow(max(0.0f, dot(h, n)), ht->getMat().get_shininess());

			color += glm::vec3((cD + cS) * light->getIntensity());
		}
	}

	// color = ht->getMat().get_ambient();
	// return glm::vec3(clamp(n.x, 0.0f, 1.0f), clamp(n.y, 0.0f, 1.0f), clamp(n.z, 0.0f, 1.0f));
	return glm::vec3(clamp(color.x, 0.0f, 1.0f), clamp(color.y, 0.0f, 1.0f), clamp(color.z, 0.0f, 1.0f));
}