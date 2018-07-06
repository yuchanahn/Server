#include "oMonsterManager.h"
#include "Base_generated.h"
#include "WriteManager.h"
#include "TimeManager.h"
#include "MysqlManager.h"

oMonsterManager::oMonsterManager()
{
	SetEventTime(SendRate);
	TimeManager::GetInstance()->AddTimeEvent(this);
}


void oMonsterManager::Start()
{
	Getinstance();
	MysqlManager m;
	auto monData = *m.GetMonsterInfo().begin();
	
	Monsters[0].Set(monData->Name, monData->startX, monData->startY, monData->Hp, monData->Exp);
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
	Monsters[0].UpdatePosition();
	flatbuffers::FlatBufferBuilder fbb;
	WriteManager::write(
		CreateMonster(fbb,
			Class::Class_Monster,
			new Vec3(Monsters[0].CurrnetPos.x, 0, Monsters[0].CurrnetPos.y),
			Monsters[0].ID,
			Monsters[0].targetID,
			new Vec3(Monsters[0].TargetPos.x, 0, Monsters[0].TargetPos.y),
			Monsters[0].AniNumber
			),
		fbb);

	TimeManager::GetInstance()->TimeReset(this);
}

oMonsterManager::~oMonsterManager()
{
}

oMonsterManager* oMonsterManager::instance = nullptr; 
std::map<int, oMonster> oMonsterManager::Monsters;
double oMonsterManager::SendRate = 0.1f;
