#include "Ping.h"
#include "WriteManager.h"
#include "ReadManager.h"
#include "Base_generated.h"
#include "TimeManager.h"

Ping::Ping()
{
	ReadManager::AddNEvent(Class::Class_ping, this);
}

Ping::~Ping()
{

}


void Ping::EventProsess(oPlayer * d, Base *d2)
{
	pingT pingData;
	flatbuffers::FlatBufferBuilder fbb;

	((ping*)d2)->UnPackTo(&pingData);
	WriteManager::write<ping>(ping::Pack(fbb, &pingData), fbb, d);
	
}

