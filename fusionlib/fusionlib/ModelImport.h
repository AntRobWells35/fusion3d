#pragma once
#include "stdafx.h"
class Mesh3D;

class ModelImport
{
public:
	ModelImport();
	virtual ~ModelImport();
	static Mesh3D * ImportObj(string path);

};

