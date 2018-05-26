#pragma once

struct Pos;
struct PlayerStat; 
struct PlayerStatT;
class Ping;
class PlayerMove;
class NetworkSpeedTest;
class cPlayerStat;
class NetEvent;


class oPlayer
{
public:
	int id;
	PlayerStatT * m_stat;

	virtual void do_writeForServer(char * str, int len);
	oPlayer();
	virtual ~oPlayer();
};

