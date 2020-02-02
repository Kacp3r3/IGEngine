#ifndef TIMER_H
#define TIMER_H
#define _CRT_SECURE_NO_WARNINGS

//================================================================
//= std Libs
//================================================================
#include <sstream>
#include <chrono>
#include <ctime>
#include <map>

//================================================================
//= my Libs
//================================================================


//================================================================
//= Time count handling
//================================================================
class Timer
{

//================================================================
//= Ctor, Dtor
//================================================================
public:
	Timer();
	~Timer();


//================================================================
//= Interface
//================================================================
	bool delay(std::string name, float secs, bool gametime);
	void Mark();
	void Reset();
	void refresh(bool ingame);
	std::string date();

//================================================================
//= Getters
//================================================================
	bool CheckState(std::string name);
	float getDelta();
	float getSingleFrameTime();
	float getFPS();
	float getDelay(std::string name);

//================================================================
//= Members
//================================================================
private:
	float m_fDelta;
	float m_fMaxFPS;
	float m_fSingleFrame;
	std::chrono::steady_clock::time_point m_current;
	std::chrono::steady_clock::time_point m_last;
	std::map<std::string, std::pair<float, bool>> m_mapTimeCounter;
};
#endif

