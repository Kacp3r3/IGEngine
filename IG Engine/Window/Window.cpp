#include "Window.h"

Window::Window(int w, int h, std::string title)
	:
	 m_nHeight(h)
	,m_nWidth(w)
{
	//Create Window
	m_pWnd.reset(glfwCreateWindow(w, h, title.c_str(), NULL, NULL));
	
	//Exception handling
	if (!m_pWnd)
		throw IGEXCEPTION_WND("Window creation failed");

	//Set necessary options
	glfwMakeContextCurrent(m_pWnd.get());
	glfwSetWindowTitle(m_pWnd.get(),title.c_str());
}

void Window::initRenderer()
{
	m_pGfx = std::make_unique<Renderer>(m_nWidth,m_nHeight);
	if(m_pGfx == nullptr) throw IGEXCEPTION_WND("Renderer creation failed");
}

GLFWwindow* Window::getWnd()
{
	return m_pWnd.get();
}

Window::Exception::Exception(int line, const char* file, const char* what) noexcept
	:
	IGException(line,file,what)
{}

const char* Window::Exception::getType() const noexcept
{
	return "Window IGException";
}

