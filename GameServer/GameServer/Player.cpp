#include "Player.h"
#include "Base_generated.h"
#include "PlayerMove.h"
#include "ReadManager.h"
#include "Monster.h"
#include "PlayerComponent.h"


void oPlayer::do_writeForServer(char * str, int len)
{

}




oPlayer::oPlayer()
{
	Components = new PlayerComponent;
}


oPlayer::~oPlayer()
{
	OnEvent("missingTarget");
}