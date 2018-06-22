#pragma once
#include "NetEvent.h"

class oPlayer;
class SendMeStatT;


class StatSendManager : public NetEvent
{
public:
	virtual void EventProsess(oPlayer * d, Base * d2);
	StatSendManager();
	~StatSendManager();


	void sPlayerStat(oPlayer*, SendMeStatT*);
	void sMonsterStat(oPlayer*, SendMeStatT*);
};