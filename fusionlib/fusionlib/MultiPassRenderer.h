#pragma once
#include "stdafx.h"
#include "fusehead.h"

class GraphRenderer;


class MultiPassRenderer :
	public GraphRenderer
{
public:
	MultiPassRenderer();
	virtual ~MultiPassRenderer();
};

