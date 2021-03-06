#pragma once
class Mesh3D
{
public:
	Mesh3D();
	Mesh3D(int verts, int indices);
	virtual ~Mesh3D();
	VertexBuffer * GetVB() {
		return VB;
	}
	int VertexCount() {
		return numVert;
	}
	int IndexCount() {
		return numInd;
	}
	void Finalize() {
		
		VB->CreateBuffer();
		Texture2D * tex1 = new Texture2D("c:/media/chalet.jpg");

		FX = new Effect("C:/Dev/Git/fusion3d_1/fusionlib/x64/Debug/shaders/basic2Dvert.spv", "C:/Dev/Git/fusion3d_1/fusionlib/x64/Debug/shaders/basic2Dfrag.spv", FusionApp::GetApp());
		Pipe = new GraphicsPipeline(FusionApp::GetApp(), FX, VB,tex1);
		FusionApp::GetApp()->SetPipe(Pipe);
		cout << "Finalized mesh" << endl;
	}
	GraphicsPipeline * GetPipe() {
		return Pipe;
	}
private:
	Effect * FX;
	GraphicsPipeline *Pipe;
	VertexBuffer * VB;
	VertexBuffer * VB2;
	int numVert, numInd;
};

