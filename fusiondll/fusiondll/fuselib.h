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
	//GraphScene * g1 = new GraphScene();
//	Entity * e1 = ModelImport::ImportEntity("c:/media/chalet.obj");
	//g1->SetRoot(e1);
//	SetScene(g1);
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
	
	Link->InitFusion();
	Link->InitApp();
	Link->ResizeApp();
	//cout << "Begining App." << endl;

//	Link->Run();

}

DO void BeginLoop() {
	glfwPollEvents();


}

DO void EndLoop() {

	vkWaitForFences(AppDev, 1, &FinFlightFences[currentFrame], VK_TRUE, std::numeric_limits<uint64_t>::max());
	vkResetFences(dev, 1, &inFlightFences[currentFrame]);

	uint32_t imageIndex;
	VkResult result = vkAcquireNextImageKHR(dev, swapChain, std::numeric_limits<uint64_t>::max(), imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

	if (result == VK_ERROR_OUT_OF_DATE_KHR) {
		recreateSwapChain();
		return;
	}
	else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
		throw std::runtime_error("failed to acquire swap chain image!");
	}


	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = 1;

	auto cbs = Pipe->GetGpus();


	submitInfo.pCommandBuffers = cbs[imageIndex]->GetBuffer();

	VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	vkResetFences(dev, 1, &inFlightFences[currentFrame]);

	if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
		throw std::runtime_error("failed to submit draw command buffer!");
	}

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = { swapChain };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;

	presentInfo.pImageIndices = &imageIndex;

	result = vkQueuePresentKHR(presentQueue, &presentInfo);

	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
		recreateSwapChain();
		framebufferResized = false;
	}
	else if (result != VK_SUCCESS) {
		throw std::runtime_error("failed to present swap chain image!");
	}

	currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;

}

DO void * CreateEntity(string path) {
	return (void *)new Entity();
}

DO Entity * LoadEntity(const char * path) {
	cout << "Importing<<" << endl;
	Entity * r= ModelImport::ImportEntity(* new string(path));
	cout << "Imported." << endl;
	return r;
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
