#pragma once
class Mesh3D
{
public:
	Mesh3D();
	virtual ~Mesh3D();
	void SetTest() {
		VB = new VertexBuffer(3, 0);
		
		Vertex v1, v2, v3, v4;

		v1.pos = { 0.0f,-0.5f,0.0f };
		v2.pos = { 0.5f,0.5f,0.0f };
		v3.pos = { -0.5f,0.5f,0.0f };
		v1.col = { 1,1,1 };
		v2.col = { 0.5,0.5,0.5 };
		v3.col = { 1,1,1 };

		VB->SetVertex(0, v1);
		VB->SetVertex(1, v2);
		VB->SetVertex(2, v3);

		VB->CreateBuffer();

		FX = new Effect("C:/Dev/Git/fusion3d/fusionlib/x64/Debug/shaders/basic2Dvert.spv", "C:/Dev/Git/fusion3d/fusionlib/x64/Debug/shaders/basic2Dfrag.spv", FusionApp::GetApp());
		Pipe = new GraphicsPipeline(FusionApp::GetApp(), FX, VB);
		FusionApp::GetApp()->SetPipe(Pipe);
	}
	GraphicsPipeline * GetPipe() {
		return Pipe;
	}
private:
	Effect * FX;
	GraphicsPipeline *Pipe;
	VertexBuffer * VB;
};

