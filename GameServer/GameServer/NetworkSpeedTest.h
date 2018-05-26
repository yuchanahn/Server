#pragma once
#include "NetEvent.h"
class NetworkSpeedTest : public NetEvent
{
	int n=1;
public:
	NetworkSpeedTest();
	~NetworkSpeedTest();
	virtual void EventProsess(oPlayer * d, Base * d2);
};

