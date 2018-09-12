#include "stdafx.h"
#include "ModelImport.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

ModelImport::ModelImport()
{
}


ModelImport::~ModelImport()
{
}

Mesh3D * ModelImport::ImportObj(string path) {

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str())) {
		throw std::runtime_error(err);
	}
	return nullptr;
//	Mesh3D * mesh = new Mesh3D();
	//return mesh;


}