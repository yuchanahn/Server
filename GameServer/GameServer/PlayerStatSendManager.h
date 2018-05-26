#pragma once
#include "NetEvent.h"

class oPlayer;

class PlayerStatSendManager : public NetEvent
{
public:
	virtual void EventProsess(oPlayer * d, Base * d2);
	PlayerStatSendManager();
	~PlayerStatSendManager();
};

