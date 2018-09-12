#pragma once
#include "stdafx.h"

class Mesh3D;

class Entity
{
public:
	Entity();
	virtual ~Entity();
	void AddMesh(Mesh3D * mesh);
	void AddSub(Entity * ent);
	Mesh3D * GetMesh(int index) {
		return meshes[0];
	}
	Entity * GetSub(int index) {
		return sub[index];
	}
	
private:
	std::vector<Entity *> sub;
	std::vector<Mesh3D *> meshes;
	glm::mat4 rotation;
	glm::vec3 scale;
	glm::vec3 position;
};


