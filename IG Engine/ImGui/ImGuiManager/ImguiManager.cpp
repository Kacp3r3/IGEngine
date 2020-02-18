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