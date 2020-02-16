#include "Input.h"
Input::Input()
	:
	 m_umapKeys()
{}
KeyState Input::getKey(int key)
{
	return m_umapKeys[key];
}

void Input::resetAllKeys()
{
	for (auto& k : m_umapKeys)
		k.second = KeyState::RELEASED;
}

bool Input::empty()
{
	return m_queueEvents.size()<1;
}

Event Input::getEvent()
{
	Event e = m_queueEvents.front();
	m_queueEvents.pop();
	return e;
}

Keyboard::Keyboard() : Input()
{
	m_umapKeys[GLFW_KEY_W] = KeyState::RELEASED;
	m_umapKeys[GLFW_KEY_A] = KeyState::RELEASED;
	m_umapKeys[GLFW_KEY_S] = KeyState::RELEASED;
	m_umapKeys[GLFW_KEY_D] = KeyState::RELEASED;
	m_umapKeys[GLFW_KEY_P] = KeyState::RELEASED;
	m_umapKeys[GLFW_KEY_O] = KeyState::RELEASED;


	m_umapKeys[GLFW_KEY_ESCAPE] = KeyState::RELEASED;
}

void Keyboard::update(int key, int scancode, int action, int mods)
{
#ifndef NDEBUG 
	if (action == GLFW_PRESS)
		printf("Kliknieto przycisk %d\n", key);
	else if (action == GLFW_REPEAT)
		printf("Przytrzymano przycisk %d\n", key);
	else
		printf("Puszczono przycisk %d\n", key);
#endif
	m_umapKeys[key] = action == GLFW_PRESS ? KeyState::PRESSED : action == GLFW_REPEAT ? KeyState::PRESSED : KeyState::RELEASED;
	//m_umapKeys[key] = action == GLFW_PRESS ? KeyState::PRESSED : action == GLFW_REPEAT ? KeyState::HELD : KeyState::RELEASED;
}

Mouse::Mouse()
	:
	Input()
	, m_fScroll(0)
	, m_bInScreen(true)
{
	m_umapKeys[GLFW_MOUSE_BUTTON_LEFT] = KeyState::RELEASED;
	m_umapKeys[GLFW_MOUSE_BUTTON_RIGHT] = KeyState::RELEASED;
	m_umapKeys[GLFW_MOUSE_BUTTON_MIDDLE] = KeyState::RELEASED;
}

void Mouse::update(int button, int action, int mods)
{
	#ifndef NDEBUG 
	if(action == GLFW_PRESS)
		printf("Kliknieto przycisk myszy %d\n", button);
	else if (action == GLFW_REPEAT)
		printf("Przytrzymano przycisk myszy %d\n", button);
	else 
		printf("Puszczono przycisk myszy %d\n", button);
	#endif
	m_umapKeys[button] = action == GLFW_PRESS ? KeyState::PRESSED : action==GLFW_REPEAT? KeyState::HELD : KeyState::RELEASED;
}

void Mouse::updatePos(double xpos, double ypos)
{
#ifndef NDEBUG 
	//printf("Ruch myszka x: %d y: %d \n", (int)xpos, (int)ypos);
#endif
	m_vecLastMouse = m_vecCurMouse;
	m_vecCurMouse = { float(xpos), float(ypos) };
	m_queueEvents.push(MOUSE_MOVE);
}

void Mouse::updateScroll(double offsetx, double offsety)
{
#ifndef NDEBUG 
	printf("Scroll offset %d \n", (int)offsety);
#endif
	m_fScroll = offsety;
	m_queueEvents.push(MOUSE_SCROLL);
}

void Mouse::updteEnter(int entered)
{
#ifndef NDEBUG 
	//printf("Cursor %s \n", entered == 1? "Entered": "Left");
#endif
	m_bInScreen = (bool)entered;
}

float Mouse::getScrollYOffset()
{
	return m_fScroll;
}

Vec2f Mouse::getPos()
{
	return m_vecCurMouse;
}

Vec2f Mouse::getDiff()
{
	return m_vecCurMouse - m_vecLastMouse;
}

bool Mouse::insideWindow()
{
	return m_bInScreen;
}

void Mouse::resetScroll()
{
	m_fScroll = 0.0f;
}
