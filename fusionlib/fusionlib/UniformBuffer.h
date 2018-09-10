#pragma once
#include "stdafx.h"

class MemBuffer;

class UniformBuffer
{
public:
	UniformBuffer(void * buf, int size);
	virtual ~UniformBuffer();
	VkDescriptorSetLayout GetVK() {
		return descriptorSetLayout;
	}
	MemBuffer * GetBuf() {
		return UBuf;
	}
private:
	VkDescriptorSetLayout descriptorSetLayout;
	MemBuffer * UBuf;
	void * buf;
};

