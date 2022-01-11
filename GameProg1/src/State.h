#pragma once
#include "Game.h"

class State
{
public:
	Game* m_Game;

	virtual void draw(const float dt) = 0;
	virtual void update(const float dt) = 0;
	virtual void input() = 0;
};
