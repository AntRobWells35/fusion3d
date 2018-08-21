#pragma once

#include "stdafx.h"

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
	virtual void InitApp() {};
	virtual void UpdateApp() {};
	virtual void RenderApp() {};
	virtual void ResizeApp() {};
	VkDevice GetDevice() {
		return dev;
	}
	VkExtent2D GetSwapExtent() { return swapChainExtent; }

private:
	
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
	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	void createSurface();
	void createLogicalDevice();
	void createSwapChain();
	void createImageViews();
	bool isDeviceSuitable(VkPhysicalDevice device);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
};

