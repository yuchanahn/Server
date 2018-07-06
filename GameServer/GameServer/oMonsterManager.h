#pragma once
#include "TimeManagerEvent.h"
#include "Monster.h"
#include "map"
#include <string>

struct CreateMonsterData
{
	std::string Name;
	int startX;
	int startY;
	int Hp;
	int Exp;

	CreateMonsterData(std::string _Name,int _startX,int _startY,int _Hp,int _Exp): 
		Name(_Name), startX(_startX), startY(_startY), Hp(_Hp), Exp(_Exp)
	{
	}
};

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

