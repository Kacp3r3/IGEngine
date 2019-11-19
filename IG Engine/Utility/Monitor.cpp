#include "Monitor.h"

Monitor::Monitor(GLFWmonitor* mon, std::string n)
	:
	 m_sName(n)
{
	glfwGetMonitorPos(mon, &m_veciPos._x, &m_veciPos._y);
	const GLFWvidmode* x = glfwGetVideoMode(mon);
	m_nHeight = x->height;
	m_nWidth = x->width;
	m_veciCenter = m_veciPos;

}

Monitor::Monitor(std::string name, int w, int h, int x, int y)
	:
	m_sName(name)
	, m_nWidth(w)
	, m_nHeight(h)
	, m_veciPos(x, y)
	, m_veciCenter(x,y)
	
{
}

void Monitor::calculateCenter(int windowW, int windowH)
{
	m_veciCenter._x = m_veciPos._x + (m_nWidth - windowW)/2;
	m_veciCenter._y = m_veciPos._y + (m_nHeight - windowH)/2;
}
