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
private:
	FusionApp * rApp;
	VkShaderModule createModule(const std::vector<char>& code, FusionApp * app);
	VkShaderModule vMod;
	VkShaderModule fMod;
	VkPipelineShaderStageCreateInfo vS, fS;
	bool useV;
	bool useF;

};

