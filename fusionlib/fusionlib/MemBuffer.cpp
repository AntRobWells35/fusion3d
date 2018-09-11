#include "stdafx.h"
#include "MemBuffer.h"


MemBuffer::MemBuffer()
{
}

void MemBuffer::MakeUniformBuffer() {
	if (!gpuMem) {
		Create(Size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT , VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, buffer, devMem);
		void* data1;
	//	vkMapMemory(FusionApp::GetApp()->GetDevice(), devMem, 0, Size, 0, &data1);
	//	memcpy(data1, rawData, (size_t)Size);
	//	vkUnmapMemory(FusionApp::GetApp()->GetDevice(), devMem);
	}
	else {
	//	Create(Size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, buffer, devMem);
	}
}

void MemBuffer::MakeVertexBuffer() {
	if (!gpuMem) {
		Create(Size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, buffer, devMem);
		void* data1;
		vkMapMemory(FusionApp::GetApp()->GetDevice(), devMem, 0, Size, 0, &data1);
		memcpy(data1, rawData, (size_t)Size);
		vkUnmapMemory(FusionApp::GetApp()->GetDevice(), devMem);
	}
	else {
		Create(Size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, buffer, devMem);

	}
}

void MemBuffer::MakeIndexBuffer() {
	if (!gpuMem) {
		Create(Size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, buffer, devMem);
		void* data1;
		vkMapMemory(FusionApp::GetApp()->GetDevice(), devMem, 0,Size, 0, &data1);
		memcpy(data1,rawData, (size_t)Size);
		vkUnmapMemory(FusionApp::GetApp()->GetDevice(), devMem);
	}
	else {
		Create(Size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, buffer, devMem);
	}
}

void MemBuffer::MakeImageBuffer() {

	if (!gpuMem) {
		Create(Size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, buffer, devMem);
		void* data;
		vkMapMemory(AppDev, devMem, 0,Size, 0, &data);
		memcpy(data, rawData, static_cast<size_t>(Size));
		vkUnmapMemory(AppDev, devMem);
	}
	else {

	}

}

void MemBuffer::Set(void * data)
{
	void* data1;
	vkMapMemory(FusionApp::GetApp()->GetDevice(), devMem, 0, Size, 0, &data1);
	memcpy(data1, data, (size_t)Size);
	vkUnmapMemory(FusionApp::GetApp()->GetDevice(), devMem);
}

MemBuffer::MemBuffer(int size,void *data,bool gpu)
{
	VkDeviceSize bufferSize = size;
	Size = bufferSize;
	gpuMem = gpu;
	rawData = data;

}


MemBuffer::~MemBuffer()
{

	vkDestroyBuffer(FusionApp::GetApp()->GetDevice(), buffer, nullptr);
	vkFreeMemory(FusionApp::GetApp()->GetDevice(), devMem, nullptr);

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

void MemBuffer::Create(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(FusionApp::GetApp()->GetDevice(), &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to create buffer!");
	}

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(FusionApp::GetApp()->GetDevice(), buffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

	if (vkAllocateMemory(FusionApp::GetApp()->GetDevice(), &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate buffer memory!");
	}

	vkBindBufferMemory(FusionApp::GetApp()->GetDevice(), buffer, bufferMemory, 0);
}
