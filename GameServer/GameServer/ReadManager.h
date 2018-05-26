#pragma once
#include <map>

class oPlayer;
class NetEvent;

class ReadManager
{

public:
	ReadManager();
	~ReadManager();
	static void AddNEvent(int e, NetEvent*);
	static void Read(char data_[1024], oPlayer * id);

	static std::map<int, NetEvent*>& GetNEvents();
};

