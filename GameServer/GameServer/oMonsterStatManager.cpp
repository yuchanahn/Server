#include "oMonsterStatManager.h"
#include "Base_generated.h"
#include "ReadManager.h"
#include "WriteManager.h"
#include "oMonsterManager.h"

void oMonsterStatManager::EventProsess(oPlayer * d, Base * d2)
{
	((MonsterStat*)d2)->UnPackTo(monStat);
	((MonsterStat*)d2)->UnPackTo(oMonsterManager::Monsters[monStat->ID].Stat);

	flatbuffers::FlatBufferBuilder fbb;
	WriteManager::write<MonsterStat>(MonsterStat::Pack(fbb, monStat), fbb);
}

oMonsterStatManager::oMonsterStatManager()
{
	monStat = new MonsterStatT;

	ReadManager::AddNEvent(Class::Class_MonsterStat, this);
}


oMonsterStatManager::~oMonsterStatManager()
{
}
