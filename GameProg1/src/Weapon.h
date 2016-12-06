#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Weapon
{
private:
	//Weapon name
	std::string m_Name;

	//Weapon damage type
	std::string m_DamageType;

	//Weapon Damage amount per attack
	int m_DamageValue;

	//Weapon ammo to start
	int m_MaxAmmo;

	//Weapon ammo currently
	int m_CurrentAmmo;

	//Weapon cool down time (in turns)
	int m_CooldownValue;
	
	//is weapon on cool down?
	bool m_IsReady;

public:
	Weapon(){}

	Weapon(std::string weaponName, std::string damageType, const unsigned int damageValue, const unsigned int maxAmmo, const unsigned int cooldownValue);

	std::string getName();

	std::string getDamageType();

	int getDamageValue();

	int getMaxAmmo();

	int getCurrentAmmo();

	void decreaseAmmo();

	bool isReady();
};