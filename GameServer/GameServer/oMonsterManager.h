#pragma once
#include "TimeManagerEvent.h"
#include "Monster.h"
#include "map"


class oMonsterManager : public TimeManagerEvent
{
	
	static oMonsterManager * instance;
	oMonsterManager();


public:

	static std::map<int, oMonster> Monsters;
	static double SendRate;


	static void Start();
	static oMonsterManager * Getinstance();
	virtual void process();



	~oMonsterManager();
};

