#include "stdafx.h"
#include "GraphicsPipeline.h"


GraphicsPipeline::GraphicsPipeline()
{
}

void GraphicsPipeline::Recreate() {

	auto app = App;
	auto fx = FX;

	Setup();

}

void GraphicsPipeline::Setup() {
	CreateInternals();
	Common::SetupPipeline(this);
	Common::BindShadersToPipeline(this, FX);

}

GraphicsPipeline::GraphicsPipeline(FusionApp * app,Effect * fx,VertexBuffer * vb,VertexBuffer * vb2)
{

	App = app;
	FX = fx;

	VB = vb;
	VB2 = vb2;
	Setup();

	createCommandBuffers();

}

void GraphicsPipeline::CreateBuffers() {
	createCommandBuffers();
}

void GraphicsPipeline::createCommandBuffers()
{

	swapChainFramebuffers = App->GetFrameBuffers();

	Gpus.resize(App->GetFrameBuffers().size());

	//GPU = new GpuChain();

	//GPU->BeginBuffer();


	for (size_t i = 0; i < Gpus.size(); i++) {
		
		Gpus[i] = new GpuChain();

		Gpus[i]->BeginBuffer();

		Gpus[i]->BeginRender(&App->GetFrameBuffers()[i], this);

		Gpus[i]->Render(VB);
		Gpus[i]->Render(VB2);

		Gpus[i]->EndRender();
		
		Gpus[i]->EndBuffer();
		
	}
	
}

GraphicsPipeline::~GraphicsPipeline()
{
	vkDestroyPipelineLayout(App->GetDevice(), pipelineLayout, nullptr);
}
