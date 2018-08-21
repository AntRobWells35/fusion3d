#pragma once

#include "stdafx.h"

//#include <string>


//using namespace std;

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
	
};

