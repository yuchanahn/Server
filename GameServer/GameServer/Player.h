#pragma once
#include "EventSystem.h"

struct Vec3;
struct Pos;
struct PlayerStat; 
struct PlayerStatT;
class Ping;
class PlayerMove;
class NetworkSpeedTest;
class cPlayerStat;
class NetEvent;
class oMonster;
class oMonsterStatManager;
class LoginManager;

class PlayerComponent;


class oPlayer : public EventSystem
{
public:
	int id;

	PlayerComponent * Components;

	PlayerStatT * m_stat;
	Vec3 * pos;
	

	virtual void do_writeForServer(char * str, int len);


	oPlayer();
	virtual ~oPlayer();
};

