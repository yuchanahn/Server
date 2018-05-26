#include "TimeManager.h" 
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>


TimeManager::TimeManager()
{
	printf("TimeThread Start!\n");

	TimeThread = new std::thread([this] {
		start = std::chrono::system_clock::now();
		while (true)
		{
			for (auto& i : TimeEvent) {
				i.second += GetTime();
			}
			for (auto& i : TimeEvent) {
				if (i.second > i.first->GetEventTime()) {
					i.first->process();
					//eraseList.push_back(i.first);
				}
			}

			for (auto i = eraseList.begin(); i != eraseList.end();) {
				TimeEvent.erase( *i );
				eraseList.erase(i++);
			}

			TEnd();
		}
	});

}

TimeManager::~TimeManager()
{
}


void TimeManager::TEnd()
{
	auto Now = std::chrono::system_clock::now();
	std::chrono::duration<double> sec = Now - start;
	endTime = sec.count();
	start = Now;
}

void TimeManager::AddTimeEvent(TimeManagerEvent* obj)
{
	TimeEvent[obj] = 0;
}

void TimeManager::Pop_TimeEvent(TimeManagerEvent* obj)
{
	TimeEvent.erase(obj);
}

double TimeManager::GetTime()
{
	return endTime;
}

void TimeManager::TimeReset(TimeManagerEvent* obj)
{
	//printf("TimeReset!\n");
	TimeEvent[obj] = 0;
}

