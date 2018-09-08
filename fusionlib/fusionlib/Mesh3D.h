#pragma once
class Mesh3D
{
public:
	Mesh3D();
	virtual ~Mesh3D();
	void SetTest() {
		VB = new VertexBuffer(4, 0);
		FX = new Effect("C:/Dev/Git/fusion3d/fusionlib/x64/Debug/shaders/basic2Dvert.spv", "C:/Dev/Git/fusion3d/fusionlib/x64/Debug/shaders/basic2Dfrag.spv", this);
		Pipe = new GraphicsPipeline(this, FX, VB);
		FusionApp::GetApp()->SetPipe(Pipe);
	}
private:
	Effect * FX;
	GraphicsPipeline *Pipe;
	VertexBuffer * VB;
};

