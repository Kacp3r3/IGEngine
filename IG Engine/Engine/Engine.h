#pragma once


#include <iostream>


#include "AssetManager/AssetManager.h"
#include "Graphics/Camera/Camera.h"
#include "Entities/Entity.h"
#include "Graphics/Light/Light.h"
#include "ImGui/ImGuiManager/ImguiManager.h"
#include "Utility\Monitor.h"
#include "Utility\Timer.h"
#include "Window\Window.h"
#include "Graphics/Camera/Camera3rd.h"
#include "Graphics/Camera/CameraFirst.h"
#include "Entities/Player/Player.h"


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
	static int SCR_WIDTH;
	static int SCR_HEIGHT;


private:
	void processInput();
	void composeFrame();
	void updateModels(float dt);

	

private:
	float checkForHeight(glm::vec2 coords);



private:
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void cursor_enter_callback(GLFWwindow* window, int entered);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void window_size_callback(GLFWwindow* window, int width, int height);

private:
	Timer m_Timer;
	ImguiManager m_Imgui;
	std::unique_ptr<Window> m_pWnd;
	std::vector<Entity*> m_vecEntities;
	Entity* SkyBox;
	Entity* stall;
	Entity* stall2;
	std::vector<Terrain*> m_vecTerrains;
	Light m_Sun;
	//Camera m_Camera;
	Camera* m_Camera;
	CameraFirst m_cf;
	Camera3rd m_ct;
	bool m_bInputEnabled;

	Player* m_Player;
};


#define IGEXCEPTION_ENG(x) Engine::Exception(__LINE__,__FILE__,x);
