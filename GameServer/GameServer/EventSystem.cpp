#include "EventSystem.h"



void EventSystem::addEvent(std::string key, std::function<void()> f)
{
	Event[key].push_back(f);
}


void EventSystem::OnEvent(std::string key)
{
	for (auto &f : Event[key]) {
		f();
	}
	Event[key].clear();
}




EventSystem::EventSystem()
{
}


EventSystem::~EventSystem()
{
}
