#pragma once
#include "Player.h"
#include "Enemy.h"

class FarOut
{
private:
	Player m_Player;
	Enemy m_Enemy;

public:
	void update(float dt);
};
