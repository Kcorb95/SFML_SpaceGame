#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
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
	std::vector<sf::Text> m_TextWeapons;

public:
	Action(Player target);

	void Attack(Player target, Weapon weapon);

	void Attack(Enemy target, Weapon weapon);
};