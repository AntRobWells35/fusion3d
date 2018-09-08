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
	void CreateBuffer();
	std::vector<Vertex> GetVertices() {
		return vertices;
	}
	std::vector<int> GetIndices() {
		return indices;
	}
	VkDeviceMemory GetBufMem() {
		return vertexBufferMemory;
	}
	VkBuffer GetBuf() {
		return vertexBuffer;
	}
private:
	std::vector<Vertex> vertices;
	std::vector<int> indices;

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;

};


