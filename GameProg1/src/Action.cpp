#include <iostream>
#include <sstream>
#include <fstream>
#include "Action.h"

Action::Action(Player target)
{
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	//Load font	
	if (!font.loadFromFile("fonts/game_sans_serif_7.ttf"))
	{
		std::cerr << "Error loading fonts/game_sans_serif_7.ttf" << std::endl;
	}

	m_Action.setFont(font);
	m_Action.setCharacterSize(25);
	m_Action.setFillColor(Color::White);
	m_Action.setPosition(resolution.x / 3, resolution.y / 1.4);
	m_Action.setString("Action:");

	m_Attack.setFont(font);
	m_Attack.setCharacterSize(20);
	m_Attack.setFillColor(Color::White);
	m_Attack.setPosition(resolution.x / 2.6, resolution.y / 1.3);
	m_Attack.setString("Attack");

	for (int i = 0; i < target.m_Weapons.size(); i++)
	{
		std::cerr << "initializing weapon names" << std::endl;
		Text weapontext;
		weapontext.setFont(font);
		weapontext.setCharacterSize(25);
		weapontext.setFillColor(Color::White);
		weapontext.setPosition(resolution.x / 2.4f, resolution.y / 1.2f + (i * 50));
		weapontext.setString(target.getWeapon(i).getName());
		m_TextWeapons.push_back(weapontext);

	}
}

void Action::Attack(Player target, Weapon weapon)
{
	target.recieveDamage(weapon.getDamageValue());
}

void Action::Attack(Enemy target, Weapon weapon)
{
	target.recieveDamage(weapon.getDamageValue());
}