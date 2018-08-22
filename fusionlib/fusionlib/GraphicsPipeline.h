#pragma once
#include "stdafx.h"
#include "fusehead.h"

class Effect;

class GraphicsPipeline
{
public:
	GraphicsPipeline();
	GraphicsPipeline(FusionApp * app,Effect * fx);
	virtual ~GraphicsPipeline();
	std::vector<VkCommandBuffer> GetCommandBuffers()
	{
		return commandBuffers;
	}
private:

	std::vector<VkFramebuffer> swapChainFramebuffers;
	std::vector<VkCommandBuffer> commandBuffers;
	void createCommandBuffers();
	FusionApp * App;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;
};

