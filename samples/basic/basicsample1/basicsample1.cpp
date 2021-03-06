// basicsample1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include "fusehead.h"

class BasicSample1 :
	public FusionApp
{
public:
	BasicSample1() : FusionApp(1024, 768, "Fusion3D - Basic Sample 1", false)
	{

	}
	void InitApp();
	void UpdateApp();
	void RenderApp();
	void ResizeApp();
private:
	Effect * testEff;
	GraphicsPipeline * testPipe;
	Mesh3D * TM;
};

void BasicSample1::InitApp() {

	//ModelImport::ImportObj("c:/media/chalet.obj");
	GraphScene * g1 = new GraphScene();
	Entity * e1 = ModelImport::ImportEntity("c:/media/chalet.obj");
	g1->SetRoot(e1);
	SetScene(g1);


	Texture2D * tex1 = new Texture2D("c:/media/chalet.jpg");
	//TM = new Mesh3D();
	//TM->SetTest()

	//SetPipe(TM->GetPipe());
}


void BasicSample1::UpdateApp() {

}

void BasicSample1::RenderApp() {

}

void BasicSample1::ResizeApp() {

}



int main()
{

	BasicSample1 * basicSample1 = new BasicSample1();

	basicSample1->Run();

	

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
