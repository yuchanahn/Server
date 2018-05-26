#include "Player.h"
#include "Base_generated.h"
#include "PlayerMove.h"
#include "ReadManager.h"




void oPlayer::do_writeForServer(char * str, int len)
{
}

oPlayer::oPlayer()
{
	m_stat = new PlayerStatT;
}


oPlayer::~oPlayer()
{
}

