#pragma once
#include <map>
#include <list>

typedef void (*EventHandler)();


enum class Event
{
	PlayerSignIn
};

class EventManager
{
	EventManager();
	std::map<Event,std::list<EventHandler>> eventHandler;
public:
	~EventManager();

	void Add(EventHandler _eventHandler, Event e);
	void OnEvent(Event e);

	static EventManager* GetInstance() {
		static EventManager * Instance = new EventManager();
		return Instance;
	}
};

