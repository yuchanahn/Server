#pragma once
#include "CPoint.h"

class oPlayer;

struct MonsterStatT;




class oMonster
{
	static int MonsterId;
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
};