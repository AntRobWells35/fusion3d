#include "stdafx.h"
#include "Effect.h"


Effect::Effect()
{

}
Effect::Effect(string vertFile, string fragFile,FusionApp * app)
{

	rApp = app;
	useV = useF = false;
	if (!(vertFile == "null"))
	{

		cout << "Loading vertex Shader:" << vertFile << endl;

		auto vertShaderCode = readFile(vertFile);
		
		vMod = createModule(vertShaderCode, app);

		useV = true;

	}

	if (!(fragFile == "null"))
	{

		cout << "Loading fragment Shader:" << fragFile << endl;

		auto fragShaderCode = readFile(fragFile);

		fMod = createModule(fragShaderCode, app);

		useF = true;

	}

	VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
	vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;

	vertShaderStageInfo.module = vMod;
	vertShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
	fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragShaderStageInfo.module = fMod;
	fragShaderStageInfo.pName = "main";

	vS = vertShaderStageInfo;
	fS = fragShaderStageInfo;

	VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputInfo.vertexBindingDescriptionCount = 0;
	vertexInputInfo.pVertexBindingDescriptions = nullptr; // Optional
	vertexInputInfo.vertexAttributeDescriptionCount = 0;
	vertexInputInfo.pVertexAttributeDescriptions = nullptr; // Optional

	VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssembly.primitiveRestartEnable = VK_FALSE;





}

VkShaderModule Effect::createModule(const std::vector<char>& code,FusionApp * app)
{
	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	VkShaderModule shaderModule;
	if (vkCreateShaderModule(app->GetDevice(), &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
		throw std::runtime_error("failed to create shader module!");
	}
	else {
		cout << "Created shader module.";
	}

	return shaderModule;

}


Effect::~Effect()
{

	vkDestroyShaderModule(rApp->GetDevice(), vMod, nullptr);
	vkDestroyShaderModule(rApp->GetDevice(), fMod, nullptr);


}
