#include "stdafx.h"
#include "FusionApp.h"


FusionApp::FusionApp() {

}

FusionApp::FusionApp(int winWidth,int winHeight,string title,bool fullScreen)
{

	WinWidth = winWidth;
	WinHeight = winHeight;
	WinTitle = WinTitle;
	WinFull = fullScreen;
	
}


FusionApp::~FusionApp()
{

	CleanUp();

}

void FusionApp::CreateInstance() {

	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = WinTitle.c_str();
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "Fusion3D";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;

	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;

	createInfo.enabledLayerCount = 0;

	if (vkCreateInstance(&createInfo, nullptr, &vInstance) != VK_SUCCESS) {
		throw std::runtime_error("failed to create instance!");
	}

	cout << "Vulkan Initialized properly." << endl;

	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> extensions(extensionCount);

	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	std::cout << "available extensions:" << std::endl;

	for (const auto& extension : extensions) {
		std::cout << "\t" << extension.extensionName << std::endl;
	}


}

void FusionApp::InitVulkan() {


	CreateInstance();


}

void FusionApp::Run() {

	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	Win = glfwCreateWindow(WinWidth, WinHeight, WinTitle.c_str() , nullptr, nullptr);


	InitVulkan();


	RunApp();


}

void FusionApp::RunApp()
{

	while (!glfwWindowShouldClose(Win)) {
		glfwPollEvents();
	}

}

void FusionApp::CleanUp() {

	vkDestroyInstance(vInstance, nullptr);

	glfwDestroyWindow(Win);

	glfwTerminate();

}