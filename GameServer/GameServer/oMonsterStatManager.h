#pragma once
#include "NetEvent.h"

struct MonsterStatT;


class oMonsterStatManager : public NetEvent
{
	MonsterStatT * monStat;
public:
	virtual void EventProsess(oPlayer * d, Base * d2);

	oMonsterStatManager();
	~oMonsterStatManager();
};

