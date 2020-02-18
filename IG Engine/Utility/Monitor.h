#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>


#include "Utility/Vec2.h"


class Monitor
{
public:
	Monitor(GLFWmonitor* mon, std::string n);
	Monitor(std::string name, int w, int h, int x, int y);
	~Monitor() = default;

public:
	void calculateCenter(int windowW,int windowH);


public:
	std::string m_sName;
	int m_nWidth;
	int m_nHeight;
	Vec2i m_veciPos;
	Vec2i m_veciCenter;
};

