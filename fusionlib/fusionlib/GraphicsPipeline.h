#pragma once
#include "stdafx.h"
#include "fusehead.h"

class Effect;
class VertexBuffer;
class GpuChain;

class GraphicsPipeline
{
public:
	GraphicsPipeline();
	GraphicsPipeline(FusionApp * app, Effect * fx, VertexBuffer *vb);
	virtual ~GraphicsPipeline();
	VkPipeline GetPipeline() {
		return graphicsPipeline;
	}
	VkPipeline * GetGraphicsPipeline() {
		return &graphicsPipeline;
	}
	VkPipelineLayout *GetPipelineLayout() {
		return &pipelineLayout;
	}

	VkPipelineLayout * GetLayout() {
		return &pipelineLayout;
	}
	void CreateBuffers();
	void Recreate();
	void CreateInternals() {
		
		viewport = {};
		scissor = {};
		viewportState = {};
		rasterizer = {};
		multisampling = {};
		colorBlendAttachment = {};
		colorBlending = {};
		pipelineLayoutInfo = {};
	}
	VkViewport * GetViewport() {
		return &viewport;
	}
	VkRect2D * GetScissor() {
		return &scissor;
	}
	VkPipelineViewportStateCreateInfo * GetViewportState() {
		return &viewportState;
	}
	VkPipelineRasterizationStateCreateInfo * GetRasterizer() {
		return &rasterizer;
	}
	VkPipelineMultisampleStateCreateInfo * GetMultiSampling() {
		return &multisampling;
	}
	VkPipelineColorBlendAttachmentState * GetColorblendAttachment() {
		return &colorBlendAttachment;
	}
	VkPipelineColorBlendStateCreateInfo * GetColorblending() {
		return &colorBlending;
	}
	VkPipelineLayoutCreateInfo * GetLayoutInfo() {
		return &pipelineLayoutInfo;
	}
	vector<GpuChain *> GetGpus() {
		return Gpus;
	}
private:
	void Setup();
	std::vector<VkFramebuffer> swapChainFramebuffers;
	std::vector<GpuChain *> Gpus;
	std::vector<MemBuffer *> Uniforms;
	void createCommandBuffers();
	FusionApp * App;
	Effect * FX;
	VertexBuffer * VB;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;
	UniformBinder * binder;
	VkViewport viewport;
	VkRect2D scissor;
	VkPipelineViewportStateCreateInfo viewportState;
	VkPipelineRasterizationStateCreateInfo rasterizer;
	VkPipelineMultisampleStateCreateInfo multisampling;
	VkPipelineColorBlendAttachmentState colorBlendAttachment;
	VkPipelineColorBlendStateCreateInfo colorBlending;
	VkPipelineLayoutCreateInfo pipelineLayoutInfo;
//	GpuChain * GPU;
};

