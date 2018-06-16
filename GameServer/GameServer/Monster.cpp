#include "Monster.h"
#include "Base_generated.h"
#include "ClientSession.h"
#include "oMonsterManager.h"

#include <stdlib.h>
#include <time.h>



oMonster::oMonster()
{
	moveTime = 2.0f;
	m_time = moveTime;

	Range = 5; 
	RandRange = 20;
	MaxRange = 2.0f;

	target = nullptr;
	ID = MonsterId++;
}

oMonster::oMonster(int _MonsterCodeID, double _moveTime, int _RandRange, double _Range, double _MaxRange)
	: MonsterCodeID(_MonsterCodeID), moveTime(_moveTime) , RandRange(_RandRange), Range(_Range), MaxRange(_MaxRange){}

oMonster::~oMonster()
{

}

void oMonster::UpdatePosition()
{
	srand(time(NULL));
	bool isTargetIn = false;

	for (auto &PlayerObj : session::GetSession()) {
		CPoint<double> TargetPlayerPos(PlayerObj.second->pos->x(), PlayerObj.second->pos->z());
		S = GetDistance(TargetPlayerPos, CurrnetPos);

		if ((Range >= S) && (TargetPlayerPos.x && TargetPlayerPos.y)) {
			TargetPos.Set(TargetPlayerPos);

			if(target != nullptr)
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

	if (target == nullptr || !isTargetIn) {
		if (m_time >= moveTime) {
			m_time = 0;
			TargetPos.Set(rand() % RandRange + 1, rand() % RandRange + 1);
		}
		S = GetDistance(TargetPos, CurrnetPos);
		m_time += oMonsterManager::SendRate;
	}

	if (MaxRange < S) {						
		CurrnetPos.x += ((TargetPos.x - CurrnetPos.x) / S);
		CurrnetPos.y += ((TargetPos.y - CurrnetPos.y) / S);
	}

	
	targetID = -1;
	if (target != nullptr) {
		targetID = target->id;
	}
}

int oMonster::MonsterId;