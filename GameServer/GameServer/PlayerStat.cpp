#include "PlayerStat.h"
#include "Base_generated.h"
#include "ReadManager.h"
#include "WriteManager.h"

void cPlayerStat::EventProsess(oPlayer * d, Base * d2)
{
	// 그냥 에코네...
	((PlayerStat*)d2)->UnPackTo(pStat);
	((PlayerStat*)d2)->UnPackTo(d->m_stat);
	flatbuffers::FlatBufferBuilder fbb;
	WriteManager::write<PlayerStat>(PlayerStat::Pack(fbb, pStat), fbb);
}

cPlayerStat::cPlayerStat()
{
	pStat = new PlayerStatT;

	ReadManager::AddNEvent(Class::Class_PlayerStat, this);
}

cPlayerStat::~cPlayerStat()
{
}
