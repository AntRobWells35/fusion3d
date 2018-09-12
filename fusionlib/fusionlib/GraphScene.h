#pragma once
#include "stdafx.h"
#include "fusehead.h"

class Entity;

class GraphScene
{
public:
	GraphScene();
	~GraphScene();
	void SetRoot(Entity * ent)
	{
		Root = ent;
	}
	Entity * GetRoot() {
		return Root;
	}
private:
	GraphRenderer * Renderer;
	Entity * Root;
};


