#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/fwd.hpp>

#include "Image.h"
#include "Camera.h"
#include "Ray.h"
#include "Material.h"
#include "Scene.h"
#include "Shape.h"
// #include "Sphere.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
using namespace std;

shared_ptr<Scene> scene1, scene2, scene3;

vector<shared_ptr<Scene>> init()
{
	/* scene 1&2 */
	shared_ptr<Sphere> redSphere = make_shared<Sphere>(glm::vec3(-0.5f, -1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
	Material mat1(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.5f), glm::vec3(0.1f, 0.1f, 0.1f), 100.0f);
	redSphere->setMat(mat1);

	shared_ptr<Sphere> greenSphere1 = make_shared<Sphere>(glm::vec3(0.5f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
	Material mat2(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.5f), glm::vec3(0.1f, 0.1f, 0.1f), 100.0f);
	greenSphere1->setMat(mat2);

	shared_ptr<Sphere> blueSphere = make_shared<Sphere>(glm::vec3(0.0f, 1.0f, 0.0f)/*glm::vec3(0.0f, 0.0f, 0.0f)*/, glm::vec3(0.2f, 0.2f, 0.2f), 1.0f);
	Material mat3(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.5f), glm::vec3(0.1f, 0.1f, 0.1f), 100.0f);
	blueSphere->setMat(mat3);

	shared_ptr<Light> light1 = make_shared<Light>(glm::vec3(-2.0, 1.0, 1.0), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);

	shared_ptr<Scene> scene1 = make_shared<Scene>();
	scene1->addShape(redSphere); // red
	scene1->addShape(greenSphere1); // green
	scene1->addShape(blueSphere); // blue
	scene1->addLight(light1);

	/* scene 3 */
	shared_ptr<Sphere> greenSphere2 = make_shared<Sphere>(glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
	greenSphere2->setMat(mat2);

	glm::mat4 ellipsoid_E(0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.6f, 0.0f, 0.0f,
		0.0f, 0.f, 0.2f, 0.0f,
		0.5f, 0.0f, 0.5f, 1.0f);
	shared_ptr<Ellipsoid> redEllipsoid = make_shared<Ellipsoid>(glm::vec3(0.5, 0.0, 0.5), glm::vec3(0.5, 0.6, 0.2), ellipsoid_E);
	redEllipsoid->setMat(mat1);

	shared_ptr<Light> light2 = make_shared<Light>(glm::vec3(1.0f, 2.0f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);
	shared_ptr<Light> light3 = make_shared<Light>(glm::vec3(-1.0f, 2.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);

	shared_ptr<Plane> plane1 = make_shared<Plane>(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Material mat4(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.1f, 0.1f), 0.0f);
	plane1->setMat(mat4);

	shared_ptr<Scene> scene3 = make_shared<Scene>();
	scene3->addShape(greenSphere2);
	scene3->addShape(redEllipsoid);
	scene3->addShape(plane1);
	scene3->addLight(light2);
	scene3->addLight(light3);

	/* Scene 4&5 */
	shared_ptr<Sphere> redSphere2 = make_shared<Sphere>(glm::vec3(0.5f, -0.7f, 0.5f), glm::vec3(0.3f, 0.3f, 0.3f), 0.3f);
	redSphere2->setMat(mat1);

	shared_ptr<Sphere> blueSphere2 = make_shared<Sphere>(glm::vec3(1.0f, -0.7f, 0.0f), glm::vec3(0.3f, 0.3f, 0.3f), 0.3f);
	blueSphere2->setMat(mat3);

	shared_ptr<Sphere> reflSphere1 = make_shared<Sphere>(glm::vec3(-0.5f, 0.0f, -0.5f) /*glm::vec3(0.0f, 0.0f, 0.0f)*/, glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, true);
	shared_ptr<Sphere> reflSphere2 = make_shared<Sphere>(glm::vec3(1.5f, 0.0f, -1.5f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, true);
	Material blackMat(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f);
	reflSphere1->setMat(blackMat);
	reflSphere2->setMat(blackMat);

	shared_ptr<Light> light4 = make_shared<Light>(glm::vec3(-1.0f, 2.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);
	shared_ptr<Light> light5 = make_shared<Light>(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);

	shared_ptr<Plane> wall = make_shared<Plane>(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	wall->setMat(mat4);

	shared_ptr<Scene> scene4 = make_shared<Scene>();
	scene4->addShape(redSphere2);
	scene4->addShape(blueSphere2);
	scene4->addShape(reflSphere1);
	scene4->addShape(reflSphere2);
	scene4->addShape(plane1);
	scene4->addShape(wall);
	scene4->addLight(light4);
	scene4->addLight(light5);

	/* scenes 6&7 */
	shared_ptr<Light> light6 = make_shared<Light>(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);

	vector<shared_ptr<Scene>> scenes;
	scenes.push_back(scene1);
	scenes.push_back(scene3);
	scenes.push_back(scene4);
	return scenes;
}

int main(int argc, char **argv)
{
	if(argc < 2) {
		cout << "Usage: A1 meshfile" << endl;
		return 0;
	}
	string scene(argv[1]);
	string size(argv[2]);
	string filename(argv[3]);

	cout << "fml" << endl;

	float fov = M_PI / 4;
	auto camera = make_shared<Camera>(glm::vec3(0.0f, 0.0f, 5.0f), -fov, stoi(size));
	shared_ptr<Image> image = make_shared<Image>(stoi(size), stoi(size));

	vector<shared_ptr<Scene>> scenes = init();

	switch (stoi(scene))
	{
		case 1: 
			cout << "case 1" << endl;
			camera->generateRays(glm::vec3(0.0f, 0.0f, 4.0f), image, scenes.at(0), false);
			break;
		case 2:
			camera->generateRays(glm::vec3(0.0f, 0.0f, 4.0f), image, scenes.at(0), false);
			break;
		case 3:
			camera->generateRays(glm::vec3(0.0f, 0.0f, 4.0f), image, scenes.at(1), false);
			break;
		case 4:
			camera->generateRays(glm::vec3(0.0f, 0.0f, 4.0f), image, scenes.at(2), true);
			break;
		case 5:
			camera->generateRays(glm::vec3(0.0f, 0.0f, 4.0f), image, scenes.at(2), true);
			break;
		case 6:
			camera->generateRays(glm::vec3(0.0f, 0.0f, 4.0f), image, scenes.at(3), false);
			break;
		case 7:
			camera->generateRays(glm::vec3(0.0f, 0.0f, 4.0f), image, scenes.at(3), false);
			break;
	}

	image->writeToFile(filename);
	
	return 0;
}

