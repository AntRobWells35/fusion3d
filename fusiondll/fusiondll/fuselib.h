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
	
	//cout << "Begining App." << endl;

//	Link->Run();

}

DO void * CreateEntity(string path) {
	return (void *)new Entity();
}

DO void * LoadEntity(string path) {
	return (void *)ModelImport::ImportEntity(path);
}

DO void * CreateGraph() {
	return (void *)new GraphScene();
}

DO void GraphSetRoot(void *graph, void * ent)
{
	GraphScene * gs = (GraphScene *)graph;
	gs->SetRoot((Entity *)ent);
}

DO int EntitySubCount(Entity * ent){
	return ent->SubCount();
}

DO Entity * EntityGetSub(Entity * ent, int id)
{
	return ent->GetSub(id);
}

DO void EntityAddMesh(Entity * ent, Mesh3D * mesh) {
	ent->AddMesh(mesh);
}

DO int MeshVertexCount(Mesh3D * mesh) {
	return mesh->VertexCount();
}

DO int MeshIndexCount(Mesh3D * mesh) {
	return mesh->IndexCount();
}

DO Mesh3D * EntityGetMesh(Entity * ent, int id) {

	return ent->GetMesh(id);

}

DO Mesh3D * CreateMesh(int vertices,int indices) {
	return new Mesh3D(vertices, indices);
}

DO int EntityMeshCount(Entity * ent) {
	return ent->MeshCount();
}
