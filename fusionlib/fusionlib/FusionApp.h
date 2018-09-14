#pragma once

#include "stdafx.h"

class GraphicsPipeline;
class GraphScene;
//#include <string>



//using namespace std;

struct QueueFamilyIndices {
	int graphicsFamily = -1;
	int presentFamily = -1;

	bool isComplete() {
		return graphicsFamily >= 0 && presentFamily >= 0;
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

class FusionApp
{
public:
	FusionApp();
	FusionApp(int winWidth, int winHeight, string title, bool fullScreen);
	virtual ~FusionApp();
	void Run();
	void createDepthResources();
	virtual void InitApp() {};
	virtual void UpdateApp() {};
	virtual void RenderApp() {};
	virtual void ResizeApp() {};
	VkDevice GetDevice() {
		return dev;
	}
	VkPhysicalDevice GetPyDevice() {
		return pDev;
	}
	VkExtent2D GetSwapExtent() { return swapChainExtent; }
	VkRenderPass GetRenderPass() { return renderPass; }
	std::vector<VkFramebuffer> GetFrameBuffers();
	VkCommandPool GetCommandPool() { return commandPool; }
	void SetPipe(GraphicsPipeline *pipe)
	{
		Pipe = pipe;
	}
	static FusionApp * GetApp() {
		return GA;
	}
	bool framebufferResized = false;
	static FusionApp *GA;
	VkCommandPool GetComPool() {
		return commandPool;
	}
	VkQueue GetGraphicsQueue() {
		return graphicsQueue;
	}
	void SetScene(GraphScene * g)
	{
		Graph = g;
	}
	void InitFusion();

	
private:
	GraphScene * Graph;
	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
	VkImageView depthImageView;
	void createSyncObjects();
	GraphicsPipeline *Pipe;
	void DrawFrame();
	void CleanUp();
	void InitVulkan();
	void RunApp();
	GLFWwindow * Win;
	int WinWidth, WinHeight;
	string WinTitle;
	bool WinFull;
	void CreateInstance();
	VkInstance vInstance;
	void setupDebugCallback();
	void PickDevice();
	VkPhysicalDevice pDev;
	VkDevice dev;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
	VkSurfaceKHR surface;
	VkSwapchainKHR swapChain;
	VkCommandPool commandPool;
	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	void createSurface();
	void createLogicalDevice();
	void createSwapChain();
	void createImageViews();
	void createRenderpass();
	void createFrameBuffers();
	void createCommandPool();
	void recreateSwapChain();
	void cleanupSwapChain();
	
	bool isDeviceSuitable(VkPhysicalDevice device);
	VkRenderPass renderPass;
	
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
};


