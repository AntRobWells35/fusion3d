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

void VertexBuffer::SetIndex(int id, uint16_t index)
{
	indices[id] = index;
}


void VertexBuffer::CreateIndexBuffer() {


	indexMem = new MemBuffer(sizeof(indices[0]) * indices.size(), indices.data(), false);
	indexMem->MakeIndexBuffer();

	hardIndexMem = new MemBuffer(sizeof(indices[0]) * indices.size(), NULL, true);
	hardIndexMem->MakeIndexBuffer();

	//createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

	GpuChain *gp = new GpuChain();

	gp->Copy(indexMem, hardIndexMem);

	delete gp;

}

void VertexBuffer::CreateBuffer() {



	VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

	vertexMem = new MemBuffer(bufferSize, vertices.data(), false);
	
	vertexMem->MakeVertexBuffer();

	hardVertexMem = new MemBuffer(bufferSize, NULL, true);
	hardVertexMem->MakeVertexBuffer();

	GpuChain * gc = new GpuChain();
	gc->Copy(vertexMem, hardVertexMem);

	delete gc;

	CreateIndexBuffer();
	


}

VertexBuffer::~VertexBuffer()
{

	delete vertexMem;
	delete hardVertexMem;
	delete indexMem;
	delete hardIndexMem;

	//vkDestroyBuffer(AppDev, indexBuffer, nullptr);
	//vkFreeMemory(AppDev, indexBufferMemory, nullptr);


	//vkDestroyBuffer(FusionApp::GetApp()->GetDevice(), vertexBuffer, nullptr);

//	vkFreeMemory(FusionApp::GetApp()->GetDevice(), vertexBufferMemory, nullptr);
}
