#pragma once
#include "stdafx.h"
#include "fusehead.h"

class GraphicsPipeline;

class GraphRenderer
{
public:
	GraphRenderer();
	virtual ~GraphRenderer();
private:
	GraphicsPipeline * Pipe;
};

