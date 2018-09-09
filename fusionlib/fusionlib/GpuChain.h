#pragma once
#include "stdafx.h"

class VertexBuffer;

class GpuChain
{
public:
	GpuChain();
	virtual ~GpuChain();
	void BeginBuffer();
	void BeginRender(VkFramebuffer * fb, GraphicsPipeline *gp);
	void Render(VertexBuffer *vb);
	void EndRender();
	void EndBuffer();
	VkCommandBuffer * GetBuffer()
	{
		return &buffer;
	}

private:
	VkCommandBuffer buffer;
};


