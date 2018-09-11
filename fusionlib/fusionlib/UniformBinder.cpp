#include "stdafx.h"
#include "UniformBinder.h"


UniformBinder::UniformBinder(int count, vector<UniformBuffer *>ubuf, VkDescriptorSetLayout layout)
{

	bufs = ubuf;
	VkDescriptorPoolSize poolSize = {};
	poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSize.descriptorCount = count;

	VkDescriptorPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = 1;
	poolInfo.pPoolSizes = &poolSize;

	poolInfo.maxSets = count;

	if (vkCreateDescriptorPool(AppDev, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor pool!");
	}
	else {
		cout << "created descriptorpool" << endl;
	}

	
	
	std::vector<VkDescriptorSetLayout> layouts(count, layout);
	VkDescriptorSetAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = descriptorPool;
	allocInfo.descriptorSetCount = count;
	allocInfo.pSetLayouts = layouts.data();

	descriptorSets.resize(count);
	if (vkAllocateDescriptorSets(AppDev, &allocInfo, &descriptorSets[0]) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate descriptor sets!");
	}
	else {
		cout << "created des-sets" << endl;
	}

	for (size_t i = 0; i < count ; i++) {
		VkDescriptorBufferInfo bufferInfo = {};
		bufferInfo.buffer = ubuf[i]->GetBuf()->GetBuffer();
		bufferInfo.offset = 0;
		bufferInfo.range = ubuf[i]->GetBuf()->GetSize();

		VkWriteDescriptorSet descriptorWrite = {};
		descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrite.dstSet = descriptorSets[i];
		descriptorWrite.dstBinding = 0;
		descriptorWrite.dstArrayElement = 0;
		descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrite.descriptorCount = 1;
		descriptorWrite.pBufferInfo = &bufferInfo;
		descriptorWrite.pImageInfo = nullptr; // Optional
		descriptorWrite.pTexelBufferView = nullptr; // Optional
		vkUpdateDescriptorSets(AppDev, 1, &descriptorWrite, 0, nullptr);

	}
	size = count;
}

void UniformBinder::Update() {

	for (size_t i = 0; i < size; i++) {
		VkDescriptorBufferInfo bufferInfo = {};
		bufferInfo.buffer = bufs[i]->GetBuf()->GetBuffer();
		bufferInfo.offset = 0;
		bufferInfo.range = bufs[i]->GetBuf()->GetSize();

		VkWriteDescriptorSet descriptorWrite = {};
		descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrite.dstSet = descriptorSets[i];
		descriptorWrite.dstBinding = 0;
		descriptorWrite.dstArrayElement = 0;
		descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrite.descriptorCount = 1;
		descriptorWrite.pBufferInfo = &bufferInfo;
		descriptorWrite.pImageInfo = nullptr; // Optional
		descriptorWrite.pTexelBufferView = nullptr; // Optional
		vkUpdateDescriptorSets(AppDev, 1, &descriptorWrite, 0, nullptr);

	}

}

UniformBinder::~UniformBinder()
{

	vkDestroyDescriptorPool(AppDev, descriptorPool, nullptr);

}
