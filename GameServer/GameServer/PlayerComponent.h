#pragma once

struct Vec3;
struct PlayerStatT;

class PlayerComponent
{
public:
	PlayerStatT * m_stat;
	Vec3 * pos;

	PlayerComponent();
	~PlayerComponent();
};

