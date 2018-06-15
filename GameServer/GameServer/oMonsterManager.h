#pragma once
#include "TimeManagerEvent.h"
#include "Monster.h"

class oMonsterManager : public TimeManagerEvent
{
	
	static oMonsterManager * instance;
	oMonsterManager();

	oMonster mon;

public:

	static double SendRate;


	static void Start();
	static oMonsterManager * Getinstance();
	virtual void process();



	~oMonsterManager();
};

