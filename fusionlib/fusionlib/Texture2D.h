#pragma once
#include "stdafx.h"
#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>

class MemBuffer;

class Texture2D
{
public:
	Texture2D();
	Texture2D(string path);
	virtual ~Texture2D();
	VkImageView GetView() {
		return imgView;
	}
	VkSampler GetSampler() {
		return imgSam;
	}
private:
	MemBuffer * memBuf;
	VkImage  img;
	VkDeviceMemory imgMem;
	MemBuffer * gpuBuf;
	VkImageView imgView;
	VkSampler imgSam;
};

