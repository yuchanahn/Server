#pragma once
class oPlayer;
class NetworkStartManager
{
public:
	static void NetStart(oPlayer * id);

	NetworkStartManager();
	~NetworkStartManager();
};

