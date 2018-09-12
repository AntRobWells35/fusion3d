#include "stdafx.h"
#include "Entity.h"


Entity::Entity()
{
	rotation = glm::mat4(1.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	sub.resize(0);
	meshes.resize(0);
}



Entity::~Entity()
{
}

void Entity::AddSub(Entity * ent) {

	sub.resize(sub.size() + 1);
	sub[sub.size() - 1] = ent;

}

void Entity::AddMesh(Mesh3D * mesh) {
	meshes.resize(meshes.size() + 1);
	meshes[meshes.size() - 1] = mesh;
}
