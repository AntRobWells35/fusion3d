#pragma once
#include "stdafx.h"

class UniformBinder
{
public:
	UniformBinder(int count, vector<UniformBuffer *> ubuf, VkDescriptorSetLayout layout, Texture2D * diff);
	virtual ~UniformBinder();
	void Update();
	std::vector<VkDescriptorSet> GetSets() {
		return descriptorSets;
	}
private:
	
	VkDescriptorPool descriptorPool;
	VkDescriptorPoolSize poolSize;
	VkDescriptorPoolCreateInfo poolInfo;
	std::vector<VkDescriptorSet> descriptorSets;
	int size;
	vector<UniformBuffer *> bufs;
};


