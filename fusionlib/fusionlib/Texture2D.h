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
private:
	MemBuffer * memBuf;
	VkImage  img;
	MemBuffer * gpuBuf;
};

