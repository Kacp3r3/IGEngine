#pragma once
#include <iostream>
#include "..\\Entity.h"
#include "..\ImGui\imgui.h"
#include "..\ImGui\imgui_impl_glfw.h"
#include "..\ImGui\imgui_impl_opengl3.h"
#include "..\ImguiManager.h"
#include "..\Window\Window.h"
#include "..\Utility\Monitor.h"
#include "..\Utility\Timer.h"
#include "..\Model.h"
#include "..\AssetManager.h"
#include "..\CameraHUD.h"

class Engine
{
public:
	class Exception : public IGException
	{
	public:
		Exception(int line, const char* file, const char* what) noexcept;
	private:
		const char* getType()const noexcept override;
	};

public:
	//================================================================
	//= Constructor Crew
	//================================================================
	Engine();
	~Engine();
	Engine(const Engine&) = delete;
	Engine(const Engine&&) = delete;
	Engine& operator = (const Engine&) = delete;
	Engine& operator = (const Engine&&) = delete;



	//================================================================
	//= Interface
	//================================================================
	int Go();



	static constexpr int SCR_WIDTH = 1280;
	static constexpr int SCR_HEIGHT = 720;
private:
	void processInput();
	void composeFrame();
	void updateModels(float dt);

	//================================================================
	//= Callbacks
	//================================================================
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void cursor_enter_callback(GLFWwindow* window, int entered);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	

private:
	Timer m_Timer;
	ImguiManager imgui;
	std::unique_ptr<Window> m_pWnd;
	std::string m_sWindowName;
	Model* cube;
	Model* SkyBox;
	CameraHUD* m_CameraHUD;
	Camera m_Camera;
	Shader* m_Shader;
	Shader* m_SkyBoxShader;
	glm::mat4 m_matProj;
	float sensitivity= 0.3f;
	float vel = 5.f;
	bool m_bInputEnabled;
	float camNear = 0.1f;
	float camFar = 400.f;
};


#define IGEXCEPTION_ENG(x) Engine::Exception(__LINE__,__FILE__,x);
