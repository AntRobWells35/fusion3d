#pragma once
#include "stdafx.h"
#include "fusehead.h"

class GraphicsPipeline
{
public:
	GraphicsPipeline();
	GraphicsPipeline(FusionApp * app);
	virtual ~GraphicsPipeline();
private:
	FusionApp * App;
	VkPipelineLayout pipelineLayout;
};

