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
class FusionApp
{
public:
	FusionApp();
	FusionApp(int winWidth, int winHeight, string title, bool fullScreen);
	virtual ~FusionApp();
	void Run();
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
	void createSurface();
	void createLogicalDevice();
	bool isDeviceSuitable(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
};

