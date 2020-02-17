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


	void initRenderer();
	//================================================================
	//= Getters
	//================================================================
	GLFWwindow* getWnd();

	//================================================================
	//= Members
	//================================================================
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
/*

class MyGlWindow 
{ 
public: 
	void mouseButtonPressed(); 
}; 

//EASIER
void makeWindow() 
{ 
	GLFWwindow* glfwWindow; 
	MyGlWindow* myWindow; 
	//... Initialize everything here ...  
	
	glfwSetWindowUserPointer(glfwWindow, myWindow); 
		auto func = [](GLFWwindow w, int, int, int) 
		{ 
		static_cast<MyGlWindow*>(glfwGetWindowUserPointer(w))->mouseButtonPressed( ); 
		} 

	glfwSetMouseButtonCallback(glfwWindow, func); 
}



//BETTER
class MyGlWindow {
public:
	std::function<void(MyGlWindow*)> onClose;
	std::function<void(MyGlWindow*, int, int, int)> onMouseClick = [](auto self, int, int, int) {  };
};

void makeWindow() {
	GLFWwindow* glfwWindow;
	MyGlWindow* myWindow;

	... Initialize everything here ... 

	glfwSetWindowUserPointer(glfwWindow, myWindow);

#define genericCallback(functionName)\
        [](GLFWwindow* window, auto... args) {\
            auto pointer = static_cast<MyGlWindow*>(glfwGetWindowUserPointer(window));\
            if (pointer->functionName) pointer->functionName(pointer, args...);\
        }

	glfwSetWindowCloseCallback(glfwWindow, genericCallback(onClose));
	glfwSetMouseButtonCallback(glfwWindow, genericCallback(onMouseClick));

	myWindow->onMouseClick = [](auto self, int, int, int) {
		std::cout << "I'm such a rebel" << std::endl;
		self->onClose = [](auto self) {
			std::cout << "I'm such a rebellion" << std::endl;
		};
	};
}



*/