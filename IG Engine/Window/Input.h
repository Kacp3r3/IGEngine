#pragma once
#include <iostream>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include "..\Utility\Vec2.h"
#include "..\Utility\Enums.h"
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

protected:
	//================================================================
	//= Members
	//================================================================
	std::unordered_map<int, KeyState> m_umapKeys;
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

	Vec2f getPos();

	void resetScroll();

private:
	Vec2f m_vecfCurMouse;
	Vec2f m_vecfLastMouse;

	float m_fScroll;
	bool m_bInScreen;
};

