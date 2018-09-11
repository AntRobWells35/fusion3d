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
	void BeginBufferSingle();
	void CopyBuffer(MemBuffer *src, MemBuffer * dst);
	void CopyBufferToImage(MemBuffer * src, VkImage img, int w, int h);
	void TransistImage(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
	void Copy(MemBuffer *src, MemBuffer *dst);
	void BeginRender(VkFramebuffer * fb, GraphicsPipeline *gp);
	void Render(VertexBuffer *vb);
	void Render(VertexBuffer *vb, UniformBinder * binder, VkPipelineLayout layout, VkDescriptorSet sets);
	void EndRender();
	void EndBuffer();
	void EndBufferSingle();
	void Run();
	VkCommandBuffer * GetBuffer()
	{
		return &buffer;
	}

private:
	VkCommandBuffer buffer;
};


