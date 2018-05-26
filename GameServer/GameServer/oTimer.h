#pragma once
#include <map>
#include <list>
#include <thread>

class oTimer
{
	std::chrono::system_clock::time_point start;
public:
	oTimer();
	~oTimer();

	void Start();
	double End();

};

