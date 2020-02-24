#include "ImguiManager.h"

ImguiManager::ImguiManager()
{
	
}

ImguiManager::~ImguiManager()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImguiManager::initImGui(GLFWwindow* wnd)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	const char* glsl_version = "#version 440";
	ImGui_ImplGlfw_InitForOpenGL(wnd, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

void ImguiManager::updateDisplay(int w, int h)
{
	ImGui::GetIO().DisplaySize.x = w;
	ImGui::GetIO().DisplaySize.y = h;
}

void ImguiManager::beginFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImguiManager::endFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
