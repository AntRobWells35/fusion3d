#pragma once

#include "fusehead.h"

#ifdef FUSIONDLL_EXPORTS
#define FUSIONDLL_API __declspec(dllexport)
#else
#define FUSIONDLL_API __declspec(dllimport)
#endif

#define DO extern "C" FUSIONDLL_API 


class FusionLink : public FusionApp {
public:
	FusionLink(int width, int height, string title, bool fullscreen) : FusionApp(width, height, title, fullscreen)
	{

	}
	void InitApp();
	void UpdateApp();
	void RenderApp();
	void ResizeApp();
};


void FusionLink::InitApp()
{
	GraphScene * g1 = new GraphScene();
	Entity * e1 = ModelImport::ImportEntity("c:/media/chalet.obj");
	g1->SetRoot(e1);
	SetScene(g1);
}

void FusionLink::UpdateApp() {

}

void FusionLink::RenderApp() {

}

void FusionLink::ResizeApp() {

}


FusionLink * Link;

DO void InitFusion(int w,int h,const char * title,bool full) {

	Link = new FusionLink(w, h, *new string(title), full);
	
	cout << "Begining App." << endl;

	Link->Run();

}
