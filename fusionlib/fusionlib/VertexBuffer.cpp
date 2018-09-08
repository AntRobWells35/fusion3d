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

uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(FusionApp::GetApp()->GetPyDevice(), &memProperties);
	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			return i;
		}
	}

	throw std::runtime_error("failed to find suitable memory type!");
}

void VertexBuffer::CreateBuffer() {

	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = sizeof(vertices[0]) * vertices.size();

	bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;

	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(FusionApp::GetApp()->GetDevice() , &bufferInfo, nullptr, &vertexBuffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to create vertex buffer!");
	}

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(FusionApp::GetApp()->GetDevice(), vertexBuffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

	if (vkAllocateMemory(FusionApp::GetApp()->GetDevice(), &allocInfo, nullptr, &vertexBufferMemory) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate vertex buffer memory!");
	}

	vkBindBufferMemory(FusionApp::GetApp()->GetDevice(), vertexBuffer, vertexBufferMemory, 0);

	void* data;
	vkMapMemory(FusionApp::GetApp()->GetDevice(), vertexBufferMemory, 0, bufferInfo.size, 0, &data);
	memcpy(data, vertices.data(), (size_t)bufferInfo.size);
	vkUnmapMemory(FusionApp::GetApp()->GetDevice(), vertexBufferMemory);



}

VertexBuffer::~VertexBuffer()
{

	vkDestroyBuffer(FusionApp::GetApp()->GetDevice(), vertexBuffer, nullptr);

	vkFreeMemory(FusionApp::GetApp()->GetDevice(), vertexBufferMemory, nullptr);
}
