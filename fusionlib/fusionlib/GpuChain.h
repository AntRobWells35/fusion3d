#pragma once
#include "stdafx.h"

class VertexBuffer;
class MemBuffer;

class GpuChain
{
public:
	GpuChain();
	virtual ~GpuChain();
	void BeginBuffer();
	void Copy(MemBuffer *src, MemBuffer *dst);
	void BeginRender(VkFramebuffer * fb, GraphicsPipeline *gp);
	void Render(VertexBuffer *vb);
	void Render(VertexBuffer *vb, UniformBinder * binder, VkPipelineLayout layout, VkDescriptorSet sets);
	void EndRender();
	void EndBuffer();
	VkCommandBuffer * GetBuffer()
	{
		return &buffer;
	}

private:
	VkCommandBuffer buffer;
};


