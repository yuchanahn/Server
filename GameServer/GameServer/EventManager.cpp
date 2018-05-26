#include "EventManager.h"



EventManager::EventManager()
{
}


EventManager::~EventManager()
{

}

void EventManager::Add(EventHandler _eventHandler, Event e)
{
	eventHandler[e].push_back(_eventHandler);
}

void EventManager::OnEvent(Event e)
{
	for (auto i : eventHandler[e]) 
		i();
}


