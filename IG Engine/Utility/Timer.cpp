#include "Timer.h"
#include <iostream>



Timer::Timer() :m_fMaxFPS(75), m_current(std::chrono::system_clock::now()), m_last(std::chrono::system_clock::now()), m_fSingleFrame(1/m_fMaxFPS), m_fDelta(0.1f)
{
}


Timer::~Timer()
{
}

float Timer::getDelta()
{
	return m_fDelta;
}

float Timer::getSingleFrameTime()
{
	return m_fSingleFrame;
}

float Timer::getFPS()
{
	return 1.0f/ m_fDelta;
}

float Timer::getDelay(std::string name)
{
	return m_mapTimeCounter[name].first;
}

bool Timer::delay(std::string name, float secs, bool gametime)
{
	if (m_mapTimeCounter.find(name) == m_mapTimeCounter.end())
	{
		m_mapTimeCounter[name] = std::make_pair((float)secs, gametime);
		return true;
	}
	else
	{
		if (m_mapTimeCounter[name].first <= 0)
		{
			m_mapTimeCounter[name].first = (float)secs ;
			return true;
		}
	}

	return false;
}

void Timer::Mark()
{
	if (m_fDelta >= 1.f / m_fMaxFPS) m_fDelta = 0.f;
	m_last = m_current;
	m_current = std::chrono::system_clock::now();
	m_fDelta+= std::chrono::duration<float>(m_current - m_last).count();

}

void Timer::Reset()
{
	std::map<std::string, std::pair<float, bool>>::iterator it;

	for (it = m_mapTimeCounter.begin(); it != m_mapTimeCounter.end(); it++)
	{
		if (it->second.second == true)
			if (it->second.first > 0) it->second.first = 0;

	}
}

bool Timer::CheckState(std::string name)
{
	if (m_mapTimeCounter[name].first <= 0)
	{
		return false;
	}
	else
		return true;
}

std::string Timer::date()
{
	std::stringstream tmp;
	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);
	tmp << (now->tm_year + 1900) << '-'
		<< (now->tm_mon + 1) << '-'
		<< now->tm_mday << " "
		<< now->tm_hour << ":"
		<< now->tm_min << ":"
		<< now->tm_sec << "\n";
	return tmp.str();
}

void Timer::refresh(bool ingame)
{
	std::map<std::string, std::pair<float,bool>>::iterator it;
	
	for (it = m_mapTimeCounter.begin(); it != m_mapTimeCounter.end(); it++)
	{
		if (it->second.second == ingame)
		{

			if (it->second.first > 0) it->second.first -= (float)m_fDelta ;
		}

	}
	
}
