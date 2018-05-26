#pragma once
struct Base;
class oPlayer;

class NetEvent
{
public:
	virtual void EventProsess(oPlayer * d, Base * d2) { };

	NetEvent();
	~NetEvent();
};

