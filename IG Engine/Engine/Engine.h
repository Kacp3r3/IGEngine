#pragma once
#include <iostream>
#include "..\Window\Window.h"
#include "..\Utility\Monitor.h"
#include "..\Utility\Timer.h"
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
	~Engine() = default;
	Engine(const Engine&) = delete;
	Engine(const Engine&&) = delete;
	Engine& operator = (const Engine&) = delete;
	Engine& operator = (const Engine&&) = delete;



	//================================================================
	//= Interface
	//================================================================
	int Go();



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
	std::unique_ptr<Window> m_pWnd;
	std::string m_sWindowName;
};


#define IGEXCEPTION_ENG(x) Engine::Exception(__LINE__,__FILE__,x);
