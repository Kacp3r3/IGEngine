#include "Engine.h"

Engine::Engine()
	:
	m_sWindowName("Kacp3r3 Playground")
	,m_Timer()
{
	int w = 800;
	int h = 600;
	//================================================================
	//= Initialize GLFW and force to use 3.3 OpenGL
	//================================================================
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	//================================================================
	//= Creating the Window
	//================================================================
	m_pWnd = std::make_unique<Window>(w, h, m_sWindowName);

	// Position of the Window
	int count = 3;
	int chosen = 1;
	Monitor* m_pMonitor;
	GLFWmonitor** tmp = glfwGetMonitors(&count);
	if (chosen>count) throw IGEXCEPTION_ENG("Nie ma wybranego monitora");
	m_pMonitor = new Monitor(tmp[chosen-1], "Lewy");
	m_pMonitor->calculateCenter(w, h);
	glfwSetWindowPos(m_pWnd->getWnd(), m_pMonitor->m_veciCenter._x, m_pMonitor->m_veciCenter._y);
	glfwSetWindowUserPointer(m_pWnd->getWnd(), m_pWnd.get());

	//================================================================
	//= Glad Initialization
	//================================================================
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::exception("Failed to load glad");
	
	//std::cout << glGetString(GL_VERSION) << std::endl;

	//================================================================
	//= Callbacks
	//================================================================
	GLFWwindow* x = m_pWnd->getWnd();
	glfwMakeContextCurrent(x);
	glfwSetKeyCallback(x, key_callback);
	glfwSetMouseButtonCallback(x, mouse_button_callback);
	glfwSetCursorPosCallback(x, cursor_position_callback);
	glfwSetCursorEnterCallback(x, cursor_enter_callback);
	glfwSetScrollCallback(x, scroll_callback);
	glfwSetFramebufferSizeCallback(x, framebuffer_size_callback);

	//Input options
	//glfwSetInputMode(x, GLFW_STICKY_KEYS | GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);

	glViewport(0, 0, w, h);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	
	m_pWnd->initRenderer();
}

int Engine::Go()
{
	while (!glfwWindowShouldClose(m_pWnd->getWnd()))
	{
		//Providing delta Time
		m_Timer.Mark();
		while (m_Timer.getDelta() < m_Timer.getSingleFrameTime())
			m_Timer.Mark();

		//Updating Label name
		std::string a = m_sWindowName + " FPS: " + std::to_string((int)round(1 / m_Timer.getDelta()));
		glfwSetWindowTitle(m_pWnd->getWnd(), a.c_str());



		//================================================================
		//= GAME LOOP
		//================================================================

		//Input
		processInput();

		//UpdateModels
		updateModels(m_Timer.getDelta());

		//Render scene
		composeFrame();


		/* Swap front and back buffers */
		glfwSwapBuffers(m_pWnd->getWnd());

		/* Poll for and process events */
		m_pWnd->mouse.resetScroll();
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void Engine::processInput()
{
	if (m_pWnd->kbd.getKey(GLFW_KEY_ESCAPE) == PRESSED)
		glfwSetWindowShouldClose(m_pWnd->getWnd(),GLFW_TRUE);

	if (m_pWnd->kbd.getKey(GLFW_KEY_1) == PRESSED)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (m_pWnd->kbd.getKey(GLFW_KEY_2) == PRESSED)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Engine::composeFrame()
{
	m_pWnd->renderClear();
	m_pWnd->renderTest();
}

void Engine::updateModels(float dt)
{

}

void Engine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static_cast<Window*>(glfwGetWindowUserPointer(window))->kbd.update(key, scancode, action, mods);
}

void Engine::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	static_cast<Window*>(glfwGetWindowUserPointer(window))->mouse.updatePos(xpos, ypos);
}

void Engine::cursor_enter_callback(GLFWwindow* window, int entered)
{
	static_cast<Window*>(glfwGetWindowUserPointer(window))->mouse.updteEnter(entered);
}

void Engine::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	static_cast<Window*>(glfwGetWindowUserPointer(window))->mouse.update(button, action, mods);
}

void Engine::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	static_cast<Window*>(glfwGetWindowUserPointer(window))->mouse.updateScroll(xoffset, yoffset);
}
void Engine::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
Engine::Exception::Exception(int line, const char* file, const char* what) noexcept
	:
	IGException(line, file, what)
{}

const char* Engine::Exception::getType() const noexcept
{
	return "IGEngine Exception";
}