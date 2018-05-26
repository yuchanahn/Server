#pragma once
#include "NetEvent.h"

class Ping : public NetEvent
{
public:
	Ping();
	~Ping();

	virtual void EventProsess(oPlayer * d, Base * d2);
};