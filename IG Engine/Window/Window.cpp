#include "Window.h"

Window::Window(int w, int h, std::string title, Display display)
	:
	 m_nHeight(h)
	,m_nWidth(w)
	,m_pWnd(glfwCreateWindow(w, h, title.c_str(), NULL, NULL))
{
	//Create Window
	//m_pWnd.reset(glfwCreateWindow(w, h, title.c_str(), NULL, NULL));
	
	//Exception handling
	if (!m_pWnd)
		throw IGEXCEPTION_WND("Window creation failed");


	int count = 2;
	GLFWmonitor** tmp = glfwGetMonitors(&count);
	if (static_cast<int>(display) > count) throw IGEXCEPTION_WND(std::string("Nie ma wybranego monitora " + static_cast<int>(display)).c_str());
	
	
	m_pMonitor = new Monitor(tmp[static_cast<int>(display) - 1], "Current");
	m_pMonitor->calculateCenter(w, h);
	
	
	glfwSetWindowPos(m_pWnd.get(), m_pMonitor->m_veciCenter._x, m_pMonitor->m_veciCenter._y);
	glfwSetWindowUserPointer(m_pWnd.get(), this);
	glfwSetInputMode(m_pWnd.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowTitle(m_pWnd.get(),title.c_str());


	glfwMakeContextCurrent(m_pWnd.get());
}

Window::~Window()
{
	delete m_pMonitor;
}

void Window::initRenderer()
{
	m_pGfx = std::make_unique<Renderer>();
	if(m_pGfx == nullptr) throw IGEXCEPTION_WND("Renderer creation failed");
}

void Window::updateSize(int w, int h)
{
	m_nHeight = h;
	m_nWidth = w;
	m_pMonitor->calculateCenter(w,h);
	glfwSetWindowPos(m_pWnd.get(), m_pMonitor->m_veciCenter._x, m_pMonitor->m_veciCenter._y);
}

void Window::setMonitor(Monitor* m)
{
	m_pMonitor = m;
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

