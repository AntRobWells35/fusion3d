#pragma once
#include "stdafx.h"

class VertexBuffer
{
public:
	VertexBuffer();
	VertexBuffer(int numVertices, int numIndices);
	virtual ~VertexBuffer();
	void SetVertex(int id, Vertex vertex);
	void SetIndex(int id, uint16_t index);
	void CreateIndexBuffer();
	void CreateBuffer();
	std::vector<Vertex> GetVertices() {
		return vertices;
	}
	std::vector<uint16_t> GetIndices() {
		return indices;
	}
	VkDeviceMemory GetBufMem() {
		return vertexBufferMemory;
	}
	VkBuffer GetIndexBuf() {
		return indexBuffer;
	}
	VkBuffer GetBuf() {
		return vertexBuffer;
	}
private:
	std::vector<Vertex> vertices;
	std::vector<uint16_t> indices;

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;

	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;

};


