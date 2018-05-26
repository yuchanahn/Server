#pragma once
#include "NetEvent.h"

struct PlayerStatT;


class cPlayerStat : public NetEvent
{
	PlayerStatT * pStat;
public:
	virtual void EventProsess(oPlayer * d, Base * d2);

	cPlayerStat();
	~cPlayerStat();
};

