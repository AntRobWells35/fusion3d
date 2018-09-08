#pragma once
#include "stdafx.h"


static std::vector<char> readFile(const std::string& filename) {
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if (!file.is_open()) {
		throw std::runtime_error("failed to open file!");
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();

	return buffer;

}



class Effect
{
public:
	Effect();
	Effect(string vertFile, string fragFile, FusionApp * app);
	virtual ~Effect();
	VkPipelineShaderStageCreateInfo GetVertexStage() {
		return vS;
	}
	VkPipelineShaderStageCreateInfo GetFragStage() {
		return fS;
	}

	VkPipelineShaderStageCreateInfo * GetShaderStages()
	{
		VkPipelineShaderStageCreateInfo rv[] = { vS,fS };
		return rv;
	}
	VkPipelineVertexInputStateCreateInfo GetVertexInput() {
		return vertexInputInfo;
	}

	VkPipelineInputAssemblyStateCreateInfo GetInputAssembly() {
		return inputAssembly;
	}

private:
	FusionApp * rApp;
	VkPipelineVertexInputStateCreateInfo vertexInputInfo;
	VkPipelineInputAssemblyStateCreateInfo inputAssembly;
	VkShaderModule createModule(const std::vector<char>& code, FusionApp * app);
	VkShaderModule vMod;
	VkShaderModule fMod;
	VkPipelineShaderStageCreateInfo vS, fS;
	bool useV;
	bool useF;
	array<VkVertexInputAttributeDescription, 7> vi;
	VkVertexInputBindingDescription vd;

};

