#include "stdafx.h"
#include "Entity.h"


Entity::Entity()
{
	rotation = glm::mat4(1.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	position = glm::vec3(0.0f, 0.0f, 0.0f);
}



Entity::~Entity()
{
}

void Entity::AddMesh(Mesh3D * mesh) {
	meshes.resize(meshes.size() + 1);
	meshes[meshes.size() - 1] = mesh;
}
