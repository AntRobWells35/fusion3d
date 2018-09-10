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
	VkBuffer GetBuf() {
		return hardVertexMem->GetBuffer();
	}
	VkBuffer GetIndexBuf() {
		return hardIndexMem->GetBuffer();
	}
	VkDeviceMemory GetBufMem() {
		return hardVertexMem->GetDevMem();
	}
	VkDeviceMemory GetIndexBufMem() {
		return hardIndexMem->GetDevMem();
	}

private:
	std::vector<Vertex> vertices;
	std::vector<uint16_t> indices;

	MemBuffer * vertexMem;
	MemBuffer * hardVertexMem;
	MemBuffer * indexMem;
	MemBuffer * hardIndexMem;
	
};


