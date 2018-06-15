#pragma once
#include <map>
#include <list>
#include <functional>

class EventSystem
{
	std::map <std::string, std::list<std::function<void()> >> Event;

public:
	
	void addEvent(std::string, std::function<void()>);
	void OnEvent(std::string);

	EventSystem();
	~EventSystem();
};

