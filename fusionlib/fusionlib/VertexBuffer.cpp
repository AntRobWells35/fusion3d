#include "stdafx.h"
#include "VertexBuffer.h"


VertexBuffer::VertexBuffer()
{
}

VertexBuffer::VertexBuffer(int numVertices, int numIndices)
{

	vertices.resize(numVertices);
	indices.resize(numIndices);


}

void VertexBuffer::SetVertex(int id, Vertex vertex)
{
	vertices[id] = vertex;
}

void VertexBuffer::SetIndex(int id, int index)
{
	indices[id] = index;
}

VertexBuffer::~VertexBuffer()
{
}
