#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "player.h"
#include "enemy.h"
#include "Weapon.h"

using namespace sf;

class Action
{
private:
	Vector2f resolution;//I need to stop having so many of these
	
    //Font for action menu
	Font font;
public:
	//Text for Action, Attack
	Text m_Action;
	Text m_Attack;

	//array of weapon names
	Text m_weapons[4];

public:
	Action(Player target);

	void Action::Attack(Player target, Weapon weapon);

	void Action::Attack(Enemy target, Weapon weapon);
};