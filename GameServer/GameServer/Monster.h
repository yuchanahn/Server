#pragma once
#include "CPoint.h"

class oPlayer;





class oMonster
{
	static int MonsterId;
public:
	// == server data == //
	int ID;
	int MonsterCodeID;

	double Range;
	int RandRange;
	double MaxRange;
	double m_time;
	double moveTime;

	int targetID;

	double S;

	CPoint<double> CurrnetPos;
	CPoint<double> TargetPos;
	// ================== //


	oPlayer * target;
	oMonster();
	oMonster(int, double, int, double, double);
	~oMonster();




	void UpdatePosition();
};