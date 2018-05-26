#pragma once
#include "NetEvent.h"

struct PlayerT;
class oPlayer;


class PlayerMove : public NetEvent
{
	PlayerT* player;
	oPlayer* m_oPlayer;
public:
	void Move();
	virtual void EventProsess(oPlayer * d, Base * d2);
	PlayerMove();
	virtual ~PlayerMove();
};