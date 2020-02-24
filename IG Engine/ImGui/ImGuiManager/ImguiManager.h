#pragma once


#include <GLFW/glfw3.h>


#include "ImGui\imgui.h"
#include "ImGui\imgui_impl_glfw.h"
#include "ImGui\imgui_impl_opengl3.h"


class ImguiManager
{
public:
	ImguiManager();
	~ImguiManager();


public:
	void initImGui(GLFWwindow* wnd);
	void updateDisplay(int w, int h);


public:
	void beginFrame();
	void endFrame();
};

