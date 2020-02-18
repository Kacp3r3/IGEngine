#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <memory>

#include "Input.h"
#include "Graphics/Renderer/Renderer.h"
#include "Utility/IGException.h"


class Window
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
	Window(int w, int h, std::string title);
	~Window() = default;

public:
	void initRenderer();


public:
	GLFWwindow* getWnd();


public:
	Keyboard kbd;
	Mouse mouse;
	std::unique_ptr<Renderer> m_pGfx;


private:
	struct GLFWwindowDeleter
	{
		void operator()(GLFWwindow* ptr) {
			glfwDestroyWindow(ptr);
		}
	};
	std::unique_ptr<GLFWwindow,GLFWwindowDeleter> m_pWnd;
	int m_nHeight;
	int m_nWidth;
};


#define IGEXCEPTION_WND(x) Window::Exception(__LINE__,__FILE__,x);