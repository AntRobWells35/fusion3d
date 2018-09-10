#pragma once
class Mesh3D
{
public:
	Mesh3D();
	virtual ~Mesh3D();
	void SetTest() {
		VB = new VertexBuffer(4, 6);
		VB2 = new VertexBuffer(4, 6);
		
		Vertex v1, v2, v3, v4;

		v1.pos = { -0.5f,-0.5f,0.0f };
		v2.pos = { 0.5f,-0.5f,0.0f };
		v3.pos = { 0.5f,0.5f,0.0f };
		v4.pos = { -0.5f,0.5f,0.0f };
		v1.col = { 1,1,1 };
		v2.col = { 0.5,0.1,0.1 };
		v3.col = { 1,1,1 };
		v4.col = { 1,1,1 };




		VB->SetVertex(0, v1);
		VB->SetVertex(1, v2);
		VB->SetVertex(2, v3);
		VB->SetVertex(3, v4);

		VB->SetIndex(0, 0);
		VB->SetIndex(1, 1);
		VB->SetIndex(2, 2);

		VB->SetIndex(3, 2);
		VB->SetIndex(4, 3);
		VB->SetIndex(5, 0);

		Vertex v11, v12, v13, v14;

		v11.pos = { 0.8f,-0.5f,0.0f };
		v12.pos = { 0.9f,-0.5f,0.0f };
		v13.pos = { 0.9f,0.5f,0.0f };
		v14.pos = { 0.8f,0.5f,0.0f };
		v11.col = { 1,1,1 };
		v12.col = { 0.5,0.1,0.1 };
		v13.col = { 1,1,1 };
		v14.col = { 1,1,1 };




		VB2->SetVertex(0, v11);
		VB2->SetVertex(1, v12);
		VB2->SetVertex(2, v13);
		VB2->SetVertex(3, v14);

		VB2->SetIndex(0, 0);
		VB2->SetIndex(1, 1);
		VB2->SetIndex(2, 2);

		VB2->SetIndex(3, 2);
		VB2->SetIndex(4, 3);
		VB2->SetIndex(5, 0);


		VB->CreateBuffer();
		VB2->CreateBuffer();
		FX = new Effect("C:/Dev/Git/fusion3d_1/fusionlib/x64/Debug/shaders/basic2Dvert.spv", "C:/Dev/Git/fusion3d_1/fusionlib/x64/Debug/shaders/basic2Dfrag.spv", FusionApp::GetApp());
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
	VertexBuffer * VB2;
};

