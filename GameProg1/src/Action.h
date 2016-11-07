#pragma once
#include <SFML\Graphics.hpp>
#include "player.h"
#include "enemy.h"
#include "Weapon.h"

using namespace sf;

class Action
{
private:

public:
	Action();

	void Attack(Player target, Weapon weapon);

	void Attack(Enemy target, Weapon weapon);
};