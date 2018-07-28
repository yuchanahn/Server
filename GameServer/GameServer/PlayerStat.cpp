#include "PlayerStat.h"
#include "Base_generated.h"
#include "ReadManager.h"
#include "WriteManager.h"
#include "PlayerComponent.h"
#include "MysqlManager.h"
#include "ClientSession.h"





void cPlayerStat::EventProsess(oPlayer * d, Base * d2)
{
	MysqlManager m;
	if (d->Components->m_stat == nullptr)// 처음이라면 DB에서 불러오기.
	{
		try {


			auto stat = m.GetPlayerStat(d->id);
			auto Pos = m.GetPlayerPos(d->id);

			d->Components->m_stat = new PlayerStatT(stat);
			d->Components->pos = Pos;

			d->Components->m_stat->ID = d->id;
			d->Components->m_stat->cType = Class::Class_PlayerStat;



			// ------------------------------------------------------------------------------------ 

			FirstCharacterDataT FirstData;

			FirstData.cType = Class::Class_FirstCharacterData;



			FirstData.Pos.reset(d->Components->pos);

			FirstData.HP = stat.HP;
			FirstData.HPLim = stat.HPLim;

			FirstData.MP = stat.MP;
			FirstData.MPLim = stat.MPLim;

			FirstData.LV = stat.LV;


			flatbuffers::FlatBufferBuilder fbb;

			WriteManager::write<FirstCharacterData>(FirstCharacterData::Pack(fbb, &FirstData), fbb, d);
			//WriteManager::write<PlayerStat>(PlayerStat::Pack(fbb, d->Components->m_stat), fbb, d);
		}
		catch (std::exception e) {
			printf("@@@@@@@@ erorr : %s\n" ,  e.what());
		}
	}
	else {
		((PlayerStat*)d2)->UnPackTo(pStat);
		auto CurrentStat = session::GetSession()[pStat->ID]->Components->m_stat;
		((PlayerStat*)d2)->UnPackTo(CurrentStat);

		m.SetPlayerStat(CurrentStat);
		flatbuffers::FlatBufferBuilder fbb;
		WriteManager::write<PlayerStat>(PlayerStat::Pack(fbb, pStat), fbb);

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
