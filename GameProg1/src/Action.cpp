#include <iostream>
#include <sstream>
#include <fstream>
#include "stdafx.h"
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
	m_Action.setPosition(resolution.x / 2, resolution.y / 2);
	m_Action.setString("Action:");
	m_Attack.setFont(font);
	m_Attack.setCharacterSize(25);
	m_Attack.setFillColor(Color::White);
	m_Attack.setPosition(resolution.x / 3, resolution.y / 2);
	m_Attack.setString("Attack");

	/*
	for (int i = 0; i < target.getCurrentWeapons; i++)
	{
		m_weapons[i].setFont(font);
		m_weapons[i].setCharacterSize(25);
		m_weapons[i].setFillColor(Color::White);
		m_weapons[i].setPosition(resolution.x / 3 + 300, resolution.y / 2 + 300);
		m_weapons[i].setString(target.getWeapon(i).getName);
	}
	*/
}

void Action::Attack(Player target, Weapon weapon)
{
	target.recievePlayerDamage(weapon.getDamageValue());
}

void Action::Attack(Enemy target, Weapon weapon)
{
	target.recieveDamage(weapon.getDamageValue());
}