#pragma once
#include "CPoint.h"
#include <string>

class oPlayer;

struct MonsterStatT;
struct CreateMonsterData;



class oMonster
{
	static int MonsterId; 
	
	double fRand(double fMin, double fMax);
public:
	// == server data == //
	MonsterStatT * Stat;

	int ID;
	int MonsterCodeID;

	double Range;
	int RandRange;
	double MaxRange;
	double m_time;
	double moveTime;

	int targetID;
	float AniNumber = 0.1f;

	double S;

	CPoint<double> prevPos;
	CPoint<double> CurrnetPos;
	CPoint<double> TargetPos;
	// ================== //


	oPlayer * target;
	oMonster();
	oMonster(int, double, int, double, double);
	~oMonster();




	void UpdatePosition();
	void Set(std::string Name, int sX,int sY, int Hp, int Exp);
};