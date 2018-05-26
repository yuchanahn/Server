#pragma once
#include <map>
#include <list>
#include "./TimeManagerEvent.h"
#include <thread>
#include "oTimer.h"


class TimeManager
{
	double endTime=0;

	void TEnd();
	double GetTime();
	
	std::chrono::system_clock::time_point start;


	std::thread * TimeThread;
	

	TimeManager();
public:
	~TimeManager();

	std::map<std::string, oTimer> Timers;


	std::list<TimeManagerEvent*> eraseList;
	std::map<TimeManagerEvent*, double> TimeEvent;

	void AddTimeEvent(TimeManagerEvent*);
	void Pop_TimeEvent(TimeManagerEvent*);

	void TimeReset(TimeManagerEvent*);
	bool FindObj(TimeManagerEvent* obj) {
		for (auto i : eraseList) {
			if (i == obj) {
				return true;
			}
		}
		return false;
	}


	static TimeManager * GetInstance() {
		static TimeManager * Instace;
		if (Instace == nullptr) {
			Instace = new TimeManager();
		}
		return Instace;
	}
};

