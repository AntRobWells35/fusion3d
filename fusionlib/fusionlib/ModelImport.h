#pragma once
#include "stdafx.h"
class Mesh3D;
class Entity;

class ModelImport
{
public:
	ModelImport();
	virtual ~ModelImport();
	static Mesh3D * ImportObj(string path);
	static Entity* ImportEntity(string path);

};

