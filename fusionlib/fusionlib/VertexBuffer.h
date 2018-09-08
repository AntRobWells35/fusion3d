#pragma once
#include "stdafx.h"

class VertexBuffer
{
public:
	VertexBuffer();
	VertexBuffer(int numVertices, int numIndices);
	virtual ~VertexBuffer();
	void SetVertex(int id, Vertex vertex);
	void SetIndex(int id, int index);
private:
	std::vector<Vertex> vertices;
	std::vector<int> indices;
};

