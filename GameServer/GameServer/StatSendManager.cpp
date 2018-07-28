#include "StatSendManager.h"
#include "Base_generated.h"
#include "ReadManager.h"
#include "WriteManager.h"
#include "ClientSession.h"
#include "oMonsterManager.h"
#include "PlayerComponent.h"

void StatSendManager::EventProsess(oPlayer * d, Base * d2)
{
	SendMeStatT * Sstat;
	((SendMeStat*)d2)->UnPackTo(Sstat);

	switch (Sstat->StatDataType)
	{
	case Class::Class_PlayerStat	:sPlayerStat(d, Sstat);		break;
	case Class::Class_MonsterStat	:sMonsterStat(d, Sstat);	break;
	default:
		break;
	}
}


StatSendManager::StatSendManager()
{
	ReadManager::AddNEvent(Class::Class_SendMeStat, this);
}

StatSendManager::~StatSendManager()
{
}

void StatSendManager::sPlayerStat(oPlayer * d, SendMeStatT*Sstat)
{
	if (session::GetSession().find(Sstat->ID) == session::GetSession().end()) {
		printf("ID_none : %d\n", Sstat->ID);
		return;
	}
	flatbuffers::FlatBufferBuilder fbb;
	auto stat = session::GetSession()[Sstat->ID]->Components->m_stat;
	WriteManager::write<PlayerStat>(PlayerStat::Pack(fbb, stat), fbb, d);
}

void StatSendManager::sMonsterStat(oPlayer * d, SendMeStatT*Sstat)
{
	if (oMonsterManager::Monsters.find(Sstat->ID) == oMonsterManager::Monsters.end()) {
		printf("(monster)ID_none : %d\n", Sstat->ID);
		return;
	}
	flatbuffers::FlatBufferBuilder fbb;
	auto stat = oMonsterManager::Monsters[Sstat->ID].Stat;
	WriteManager::write<MonsterStat>(MonsterStat::Pack(fbb, stat), fbb, d);
}


