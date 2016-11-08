#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Weapon
{
private:
	//Weapon name
	String m_Name;

	//Weapon damage type
	String m_DamageType;

	//Weapon Damage ammount per attack
	int m_DamageValue;

	//Weapon ammo to start
	int m_StartingAmmo;

	//Weapon ammo currently
	int m_CurrentAmmo;

	//Weapon cooldown time (in turns)
	int m_CooldownValue;
	
	//is weapon on cooldown?
	bool m_IsReady;

public:
	Weapon(String weaponName, String damageType, int damageValue, int startingAmmo, int currentAmmo, int cooldownValue);

	String getName();

	String getDamageType();

	int getDamageValue();

	int getStartingAmmo();

	int getCurrentAmmo();

	bool isReady();
};