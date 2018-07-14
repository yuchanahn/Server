#pragma once
#include "NetEvent.h"

struct LoginT;

class LoginManager : public NetEvent
{
	LoginT * LoginData;

	
public:
	LoginManager();
	~LoginManager();

	virtual void EventProsess(oPlayer * d, Base * d2);
};

