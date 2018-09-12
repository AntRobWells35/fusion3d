#include "stdafx.h"
#include "Mesh3D.h"


Mesh3D::Mesh3D()
{
}


Mesh3D::~Mesh3D()
{
}

Mesh3D::Mesh3D(int vert, int indices)
{
	VB = new VertexBuffer(vert, indices);
	numVert = vert;
	numInd = indices;

}
