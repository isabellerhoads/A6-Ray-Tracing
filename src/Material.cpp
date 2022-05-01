#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Material.h"
#include "Light.h"
#include "Ray.h"
#include <iostream>
#include <algorithm>
#include <memory>

using namespace std;

glm::vec3 Material::get_ambient() 
{ 
	return ka; 
}

glm::vec3 Material::get_diffuse() 
{ 
	return kd; 
}

glm::vec3 Material::get_specular() 
{ 
	return ks; 
}

float Material::get_shininess() 
{ 
	return s; 
}