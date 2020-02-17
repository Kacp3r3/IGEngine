#pragma once
#include <iostream>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include "Utility\Vec2.h"
#include "Utility\Enums.h"
#include <queue>
class Input
{
protected:
	Input();

public:
	//================================================================
	//= Interface
	//================================================================
	//Defined in deriving class


	//================================================================
	//= Getters
	//================================================================
	KeyState getKey(int key);


	//================================================================
	//= Setters
	//================================================================
	void resetAllKeys();
	bool empty();
	Event getEvent();
protected:
	//================================================================
	//= Members
	//================================================================
	std::unordered_map<int, KeyState> m_umapKeys;
	std::queue<Event> m_queueEvents;
};


class Keyboard : public Input
{
public:
	Keyboard();

	//================================================================
	//= Interface
	//================================================================
	void update(int key, int scancode, int action, int mods);
};

class Mouse : public Input
{
public:
	Mouse();

	//================================================================
	//= Interface
	//================================================================

	void update(int button, int action, int mods);
	void updatePos(double xpos, double ypos);
	void updateScroll(double offsetx, double offsety);
	void updteEnter(int entered);
	float getScrollYOffset();

	Vec2f getPos();
	Vec2f getDiff();
	bool insideWindow();
	void resetScroll();

private:
	Vec2f m_vecCurMouse;
	Vec2f m_vecLastMouse;

	float m_fScroll;
	bool m_bInScreen;
	//Vec2f m_vecScrolloffset;
};

