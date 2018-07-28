#include "Monster.h"
#include "Base_generated.h"
#include "ClientSession.h"
#include "oMonsterManager.h"
#include "PlayerComponent.h"

#include <stdlib.h>
#include <float.h>
#include <time.h>


double oMonster::fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

oMonster::oMonster()
{
	moveTime = 2.0f;
	m_time = moveTime;

	Range = 5; 
	RandRange = 20;
	MaxRange = 2.0f;

	target = nullptr;

	Stat = new MonsterStatT;
	Stat->cType = Class::Class_MonsterStat;
	
	ID = MonsterId++;
	Stat->ID = ID;
	Stat->HP = 100;

	CurrnetPos.Set(0,0);
	prevPos.Set(CurrnetPos);
}

oMonster::oMonster(int _MonsterCodeID, double _moveTime, int _RandRange, double _Range, double _MaxRange)
	: MonsterCodeID(_MonsterCodeID), moveTime(_moveTime) , RandRange(_RandRange), Range(_Range), MaxRange(_MaxRange)
{

	Stat = new MonsterStatT;
	Stat->cType = Class::Class_MonsterStat;
}

oMonster::~oMonster()
{

}

void oMonster::UpdatePosition()
{
	srand(time(NULL));
	bool isTargetIn = false;

	for (auto &PlayerObj : session::GetSession()) {
		if (PlayerObj.second->Components->pos != nullptr) {
			CPoint<double> TargetPlayerPos(PlayerObj.second->Components->pos->x(), PlayerObj.second->Components->pos->z());


			S = GetDistance(TargetPlayerPos, CurrnetPos);

			if ((Range >= S) && (TargetPlayerPos.x && TargetPlayerPos.y)) {
				TargetPos.Set(TargetPlayerPos);

				if (target != nullptr)
					if (target->id != PlayerObj.second->id) {
						PlayerObj.second->addEvent("missingTarget",
							[=]() {
							if (PlayerObj.second->id == target->id) {
								target = nullptr;
							}
						}
						);
					}

				target = &(*PlayerObj.second);
				isTargetIn = true;
				break;
			}
		}
	}

	if (target == nullptr || !isTargetIn) {
		if (m_time >= moveTime) {
			m_time = 0; 
			TargetPos.Set(fRand(-RandRange, RandRange), fRand(-RandRange, RandRange));
		}
		S = GetDistance(TargetPos, CurrnetPos);
		m_time += oMonsterManager::SendRate;
	}
	

	// mysql 써가지고 데이터 관리 추가.... 


	AniNumber = 0.0f;
	if (MaxRange < S) {
		prevPos.Set(TargetPos);
		CurrnetPos.x += ((TargetPos.x - CurrnetPos.x) / S)*0.3f;
		CurrnetPos.y += ((TargetPos.y - CurrnetPos.y) / S)*0.3f;
		AniNumber = 0.1f;
	}
	

	






	
	targetID = -1;
	if (target != nullptr) {
		targetID = target->id;
	}
}

void oMonster::Set(std::string Name, int sX, int sY, int Hp, int Exp)
{
	Stat->HP = Hp;
	
}



int oMonster::MonsterId=0;