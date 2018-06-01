#pragma once
#include "TimeManagerEvent.h"


class oMonster : public TimeManagerEvent
{
	static int MonsterId;

	int ID;
	double x, y;
	double Range;
	double MaxRange; //최대 근접.
	int TargetID;

public:
	oMonster();
	~oMonster();

	virtual void process();
};