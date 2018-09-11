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

	vector<UniformBuffer *> uni;
	swapChainFramebuffers = FApp->GetFrameBuffers();

	uni.resize(swapChainFramebuffers.size());

	for (int i = 0; i < swapChainFramebuffers.size(); i++) {

		ModelViewProj test = {};
		test.model = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
		test.model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		test.proj = glm::ortho<float>(-1.0f, 1.0f, -1.0f, 1.0f, -1, 1);
		test.view = glm::mat4(1.0f);


		//uni[i] = new MemBuffer(sizeof(ModelViewProj), &test, false);
		//uni[i]->MakeUniformBuffer();



		uni[i] = new UniformBuffer(&test,sizeof(test));

	}


	for (int i = 0; i < uni.size(); i++) {
		cout << "Reseted " << i << endl;
		ModelViewProj mvp = {};
		//	test.model = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
		mvp.model = glm::rotate(glm::mat4(1.0f), glm::radians(40.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		mvp.proj = glm::ortho<float>(-1.0f, 1.0f, -1.0f, 1.0f, -1, 1);
		mvp.view = glm::mat4(1.0f);


		//uni[i] = new MemBuffer(sizeof(ModelViewProj), &test, false);
		//uni[i]->MakeUniformBuffer();

		uni[i]->Set(&mvp, sizeof(mvp));

	}

	UniBuf = uni;


	VkDescriptorSetLayoutBinding uboLayoutBinding = {};
	uboLayoutBinding.binding = 0;
	uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	uboLayoutBinding.descriptorCount = 1;
	uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
	uboLayoutBinding.pImmutableSamplers = nullptr; // Optional
	VkDescriptorSetLayoutCreateInfo layoutInfo = {};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = 1;
	layoutInfo.pBindings = &uboLayoutBinding;

	VkDescriptorSetLayout desLay;

	if (vkCreateDescriptorSetLayout(AppDev, &layoutInfo, nullptr, &desLay) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor set layout!");
	}
	else {
		cout << "Created." << endl;
	}


	

	Common::SetupPipeline(this, uni,desLay);
	Common::BindShadersToPipeline(this, FX);

	binder = new UniformBinder(swapChainFramebuffers.size(), uni, desLay);
	binder->Update();

}

GraphicsPipeline::GraphicsPipeline(FusionApp * app,Effect * fx,VertexBuffer * vb)
{

	App = app;
	FX = fx;

	VB = vb;

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
	Uniforms.resize(swapChainFramebuffers.size());

	//GPU = new GpuChain();

	//GPU->BeginBuffer();


	for (size_t i = 0; i < Gpus.size(); i++) {
		
		Gpus[i] = new GpuChain();

		Gpus[i]->BeginBuffer();

		Gpus[i]->BeginRender(&App->GetFrameBuffers()[i], this);

		Gpus[i]->Render(VB, binder, pipelineLayout, binder->GetSets()[i]);

		Gpus[i]->EndRender();
		
		Gpus[i]->EndBuffer();
		
	
	}
	
}

GraphicsPipeline::~GraphicsPipeline()
{
	vkDestroyPipelineLayout(App->GetDevice(), pipelineLayout, nullptr);
}
