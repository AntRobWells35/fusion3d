#pragma once
#include "stdafx.h"
#include "fusehead.h"

class Effect;
class VertexBuffer;

class GraphicsPipeline
{
public:
	GraphicsPipeline();
	GraphicsPipeline(FusionApp * app, Effect * fx, VertexBuffer *vb);
	virtual ~GraphicsPipeline();
	VkPipeline GetPipeline() {
		return graphicsPipeline;
	}
	VkPipelineLayout GetPipelineLayout() {
		return pipelineLayout;
	}
	std::vector<VkCommandBuffer> GetCommandBuffers()
	{
		return commandBuffers;
	}
	void CreateBuffers();
	void Recreate();
private:
	void Setup();
	std::vector<VkFramebuffer> swapChainFramebuffers;
	std::vector<VkCommandBuffer> commandBuffers;
	void createCommandBuffers();
	FusionApp * App;
	Effect * FX;
	VertexBuffer * VB;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;
};

