#pragma once


#include <iostream>
#include <unordered_map>
#include <queue>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>


#include "Utility\Vec2.h"
#include "Utility\Enums.h"


class Input
{
protected:
	Input();


public:
	void resetAllKeys();
	bool empty();


public:
	bool isPressed(int key);
	KeyState getKey(int key);
	std::pair<Event, int> getEvent();


protected:
	std::unordered_map<int, KeyState> m_umapKeys;
	std::queue<std::pair<Event,int>> m_queueEvents;
};


class Keyboard : public Input
{
public:
	Keyboard();


public:
	void update(int key, int scancode, int action, int mods);
};

class Mouse : public Input
{
public:
	Mouse();


public:
	void update(int button, int action, int mods);
	void updatePos(double xpos, double ypos);
	void updateScroll(double offsetx, double offsety);
	void updteEnter(int entered);
	bool insideWindow();
	void resetScroll();


public:
	float getScrollYOffset();
	glm::vec2 getPos();
	glm::vec2 getDiff();

private:
	glm::vec2 m_vecCurMouse;
	glm::vec2 m_vecLastMouse;
	float m_fScroll;
	bool m_bInScreen;
};

