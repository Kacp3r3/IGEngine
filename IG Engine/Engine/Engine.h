#pragma once


#include <iostream>


#include "AssetManager/AssetManager.h"
#include "Graphics/Camera/CameraHUD.h"
#include "ImGui/ImGuiManager/ImguiManager.h"
#include "Utility\Monitor.h"
#include "Utility\Timer.h"
#include "Window\Window.h"


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
	Engine();
	~Engine();
	Engine(const Engine&) = delete;
	Engine(const Engine&&) = delete;
	Engine& operator = (const Engine&) = delete;
	Engine& operator = (const Engine&&) = delete;


public:
	int Go();


public:
	static constexpr int SCR_WIDTH = 1280;
	static constexpr int SCR_HEIGHT = 720;


private:
	void processInput();
	void composeFrame();
	void updateModels(float dt);


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
	bool m_bInputEnabled;
};


#define IGEXCEPTION_ENG(x) Engine::Exception(__LINE__,__FILE__,x);
