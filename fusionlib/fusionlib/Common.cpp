#include "stdafx.h"
#include "Common.h"


Common::Common()
{
}


Common::~Common()
{
}

void Common::SetupPipeline(GraphicsPipeline * gp,vector<UniformBuffer *> uniforms,VkDescriptorSetLayout desLay) {
	
	VkViewport *viewport = gp->GetViewport();


		viewport->x = 0.0f;
		viewport->y = 0.0f;
		viewport->width = (float)FApp->GetSwapExtent().width;
		viewport->height = (float)FApp->GetSwapExtent().height;
		viewport->minDepth = 0.0f;
		viewport->maxDepth = 1.0f;

		VkRect2D *scissor = gp->GetScissor();
		scissor->offset = { 0, 0 };
		scissor->extent = FApp->GetSwapExtent();

		VkPipelineViewportStateCreateInfo *viewportState = gp->GetViewportState();
		viewportState->sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState->viewportCount = 1;
		viewportState->pViewports = viewport;
		viewportState->scissorCount = 1;
		viewportState->pScissors = scissor;

		VkPipelineRasterizationStateCreateInfo *rasterizer = gp->GetRasterizer();
		rasterizer->sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer->depthClampEnable = VK_FALSE;

		rasterizer->rasterizerDiscardEnable = VK_FALSE;

		rasterizer->polygonMode = VK_POLYGON_MODE_FILL;

		rasterizer->lineWidth = 1.0f;

		rasterizer->cullMode = VK_CULL_MODE_BACK_BIT;
		rasterizer->frontFace = VK_FRONT_FACE_CLOCKWISE;

		rasterizer->depthBiasEnable = VK_FALSE;
		rasterizer->depthBiasConstantFactor = 0.0f; // Optional
		rasterizer->depthBiasClamp = 0.0f; // Optional
		rasterizer->depthBiasSlopeFactor = 0.0f; // Optional

		VkPipelineMultisampleStateCreateInfo *multisampling = gp->GetMultiSampling();
		multisampling->sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling->sampleShadingEnable = VK_FALSE;
		multisampling->rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		multisampling->minSampleShading = 1.0f; // Optional
		multisampling->pSampleMask = nullptr; // Optional
		multisampling->alphaToCoverageEnable = VK_FALSE; // Optional
		multisampling->alphaToOneEnable = VK_FALSE; // Optional

		VkPipelineColorBlendAttachmentState *colorBlendAttachment = gp->GetColorblendAttachment();
		colorBlendAttachment->colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlendAttachment->blendEnable = VK_FALSE;
		colorBlendAttachment->srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
		colorBlendAttachment->dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
		colorBlendAttachment->colorBlendOp = VK_BLEND_OP_ADD; // Optional
		colorBlendAttachment->srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
		colorBlendAttachment->dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
		colorBlendAttachment->alphaBlendOp = VK_BLEND_OP_ADD; // Optional

		VkPipelineColorBlendStateCreateInfo *colorBlending = gp->GetColorblending();
		colorBlending->sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlending->logicOpEnable = VK_FALSE;
		colorBlending->logicOp = VK_LOGIC_OP_COPY; // Optional
		colorBlending->attachmentCount = 1;
		colorBlending->pAttachments = colorBlendAttachment;
		colorBlending->blendConstants[0] = 0.0f; // Optional
		colorBlending->blendConstants[1] = 0.0f; // Optional
		colorBlending->blendConstants[2] = 0.0f; // Optional
		colorBlending->blendConstants[3] = 0.0f; // Optional

		VkPipelineLayoutCreateInfo * pipelineLayoutInfo = gp->GetLayoutInfo();
		pipelineLayoutInfo->sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo->setLayoutCount = 1;
		pipelineLayoutInfo->pSetLayouts = &desLay;

		vector<VkDescriptorSetLayout> los;

//		los.resize(uniforms.size());

	//	for (int i = 0; i < uniforms.size(); i++) {
	//		los[i] = uniforms[i]->GetVK();
	//	}


	//	pipelineLayoutInfo->pSetLayouts = los.data();
		pipelineLayoutInfo->pushConstantRangeCount = 0;

		

		if (vkCreatePipelineLayout(FApp->GetDevice(), pipelineLayoutInfo, nullptr, gp->GetPipelineLayout()) != VK_SUCCESS) {
			throw std::runtime_error("failed to create pipeline layout!");
		}



}

void Common::BindShadersToPipeline(GraphicsPipeline *gp, Effect * fx)
{

	
	VkPipelineShaderStageCreateInfo shaderStages[] = { fx->GetVertexStage(), fx->GetFragStage() };

	VkGraphicsPipelineCreateInfo pipelineInfo = {};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = 2;
	pipelineInfo.pStages = shaderStages;
	pipelineInfo.pVertexInputState = &fx->GetVertexInput();
	pipelineInfo.pInputAssemblyState = &fx->GetInputAssembly();
	pipelineInfo.pViewportState = gp->GetViewportState();
	pipelineInfo.pRasterizationState = gp->GetRasterizer();
	pipelineInfo.pMultisampleState = gp->GetMultiSampling();
	pipelineInfo.pColorBlendState = gp->GetColorblending();
	pipelineInfo.layout = *gp->GetLayout();
	pipelineInfo.renderPass = FApp->GetRenderPass();
	pipelineInfo.subpass = 0;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;




	if (vkCreateGraphicsPipelines(FApp->GetDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, gp->GetGraphicsPipeline()) != VK_SUCCESS) {
		throw std::runtime_error("failed to create graphics pipeline!");
	}
	else {
		cout << "Created graphics pipeline" << endl;
	}
	
}