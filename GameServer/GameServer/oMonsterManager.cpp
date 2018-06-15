#include "oMonsterManager.h"
#include "Base_generated.h"
#include "WriteManager.h"
#include "TimeManager.h"

oMonsterManager::oMonsterManager()
{
	SetEventTime(SendRate);
	TimeManager::GetInstance()->AddTimeEvent(this);
}


void oMonsterManager::Start()
{
	Getinstance();
}

oMonsterManager* oMonsterManager::Getinstance()
{
	if (instance == nullptr) {
		instance = new oMonsterManager();
	}
	return instance;
}

void oMonsterManager::process()
{
	mon.UpdatePosition();
	flatbuffers::FlatBufferBuilder fbb;
	WriteManager::write(
		CreateMonster(fbb, 
			Class::Class_Monster, 
			new Vec3(mon.CurrnetPos.x, 0, mon.CurrnetPos.y),
			mon.ID,
			mon.targetID,
			new Vec3(mon.TargetPos.x, 0, mon.TargetPos.y)),
		fbb);
	TimeManager::GetInstance()->TimeReset(this);
}

oMonsterManager::~oMonsterManager()
{
}

oMonsterManager* oMonsterManager::instance = nullptr;
double oMonsterManager::SendRate = 0.1f;
