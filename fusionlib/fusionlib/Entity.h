#pragma once
#include "stdafx.h"

class Mesh3D;

class Entity
{
public:
	Entity();
	virtual ~Entity();
	void AddMesh(Mesh3D * mesh);
private:
	std::vector<Mesh3D *> meshes;
	glm::mat4 rotation;
	glm::vec3 scale;
	glm::vec3 position;
};


