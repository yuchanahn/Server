#include "ReadManager.h"
#include "Base_generated.h"
#include <iostream>
#include "Player.h"
#include "NetEvent.h"
#include "TimeManager.h"

ReadManager::ReadManager()
{
	

}


ReadManager::~ReadManager()
{
}

void ReadManager::AddNEvent(int e, NetEvent* ev)
{
	GetNEvents()[e] = ev;
}

void ReadManager::Read(char data_[1024], oPlayer * id)
{
	auto data(GetBase(data_));


	if (GetNEvents().find(data->cType()) == GetNEvents().end()) {
		printf("not real data!\nfor : %d\n", id->id);
		return;
	}


	GetNEvents()[data->cType()]->EventProsess(id, (Base*)data);
}

std::map<int, NetEvent*>& ReadManager::GetNEvents()
{
	static std::map<int, NetEvent*> NEvent;
	return NEvent;
}
