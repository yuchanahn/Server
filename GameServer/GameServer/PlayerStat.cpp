#include "PlayerStat.h"
#include "Base_generated.h"
#include "ReadManager.h"
#include "WriteManager.h"
#include "PlayerComponent.h"
#include "MysqlManager.h"





void cPlayerStat::EventProsess(oPlayer * d, Base * d2)
{
	MysqlManager m;
	if (d->Components->m_stat == nullptr)// 처음이라면 DB에서 불러오기.
	{
		auto stat = m.GetPlayerStat(d->id);
		auto Pos = m.GetPlayerPos(d->id);

		d->Components->m_stat	= new PlayerStatT(stat);
		d->Components->pos		= new Vec3(Pos); 

		d->Components->m_stat->ID		= d->id;
		d->Components->m_stat->cType	= Class::Class_PlayerStat;


		// ------------------------------------------------------------------------------------ 

		FirstCharacterDataT FirstData;

		FirstData.cType = Class::Class_FirstCharacterData;

		

		FirstData.Pos.reset(d->Components->pos);

		FirstData.HP			= stat.HP;
		FirstData.HPLim			= stat.HPLim;

		FirstData.MP			= stat.MP;
		FirstData.MPLim			= stat.MPLim;

		FirstData.LV			= stat.LV;

		
		flatbuffers::FlatBufferBuilder fbb;

		WriteManager::write<FirstCharacterData>(FirstCharacterData::Pack(fbb, &FirstData), fbb, d);
		//WriteManager::write<PlayerStat>(PlayerStat::Pack(fbb, d->Components->m_stat), fbb, d);
	}
	else {
		((PlayerStat*)d2)->UnPackTo(pStat);
		((PlayerStat*)d2)->UnPackTo(d->Components->m_stat);

		pStat->ID = d->id;

		flatbuffers::FlatBufferBuilder fbb;
		WriteManager::write<PlayerStat>(PlayerStat::Pack(fbb, pStat), fbb);

		m.SetPlayerStat(d->Components->m_stat);
	}
}

void cPlayerStat::SendStat(oPlayer * player)
{


	
}

cPlayerStat::cPlayerStat()
{
	pStat = new PlayerStatT;

	ReadManager::AddNEvent(Class::Class_PlayerStat, this);
}

cPlayerStat::~cPlayerStat()
{
}
