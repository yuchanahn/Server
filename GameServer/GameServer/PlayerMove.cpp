#include "PlayerMove.h"
#include "Base_generated.h"
#include "ReadManager.h"
#include "WriteManager.h"

void PlayerMove::Move()
{
	flatbuffers::FlatBufferBuilder fbb; 
	WriteManager::write_not_me<Player>(Player::Pack(fbb, player),fbb, m_oPlayer);
}

void PlayerMove::EventProsess(oPlayer * d, Base * d2)
{
	((Player*)d2)->UnPackTo(player);
	player->ID = d->id;
	m_oPlayer = d;

	auto DeletVal = d->pos;
	d->pos = new Vec3(player->pos->x(), player->pos->y(), player->pos->z());
	delete DeletVal;

	Move();
}

PlayerMove::PlayerMove()
{
	player = new PlayerT;

	ReadManager::AddNEvent(Class::Class_Player ,this);
}


PlayerMove::~PlayerMove()
{
}
