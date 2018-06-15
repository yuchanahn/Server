#include "PlayerStatSendManager.h"
#include "Base_generated.h"
#include "ReadManager.h"
#include "WriteManager.h"
#include "ClientSession.h"

void PlayerStatSendManager::EventProsess(oPlayer * d, Base * d2)
{ 
	SendMeStatT Sstat;
	((SendMeStat*)d2)->UnPackTo(&Sstat);
	flatbuffers::FlatBufferBuilder fbb;

	if (session::GetSession().find(Sstat.ID) == session::GetSession().end()) {
		printf("ID_none : %d\n", Sstat.ID);
		return;
	}

	auto stat = session::GetSession()[Sstat.ID]->m_stat;
	WriteManager::write<PlayerStat>(PlayerStat::Pack(fbb, stat), fbb, d);
}


PlayerStatSendManager::PlayerStatSendManager()
{
	ReadManager::AddNEvent(Class::Class_SendMeStat, this);
}



PlayerStatSendManager::~PlayerStatSendManager()
{
}
