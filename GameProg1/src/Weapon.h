#pragma once
#include <SFML/Graphics.hpp>

class Weapon
{
private:
	//Weapon name
	std::string m_Name;

	//Weapon damage type
	std::string m_DamageType;

	//Weapon Damage amount per attack
	int m_DamageValue;

	//Weapon hit chance
	int m_HitChance;

	//Weapon ammo to start
	int m_MaxAmmo;

	//Weapon ammo currently
	int m_CurrentAmmo;

	//Weapon cool down time (in turns)
	int m_CooldownValue;

	//is weapon on cool down?
	bool m_IsReady;

public:
	Weapon() {}

	Weapon(const std::string weaponName, const std::string damageType, const unsigned int damageValue, const unsigned int hitChance, const unsigned int maxAmmo, const unsigned int cooldownValue)
	{
		this->m_Name = weaponName;
		this->m_DamageType = damageType;
		this->m_DamageValue = damageValue;
		this->m_HitChance = hitChance;
		this->m_MaxAmmo = maxAmmo;
		this->m_CurrentAmmo = maxAmmo;
		this->m_CooldownValue = cooldownValue;
		this->m_IsReady = true;
	}

	std::string getName();

	std::string getDamageType();

	int getDamageValue();

	int getHitChance();

	int getMaxAmmo();

	int getCurrentAmmo();

	void decreaseAmmo();

	void increaseAmmo(int amount);

	bool isReady();
};