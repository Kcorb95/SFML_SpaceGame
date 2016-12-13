#pragma once
#include <SFML/Graphics.hpp>
#include "SoundManager.h"

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

	//Vector of sound effects a weapon can have
	std::vector<std::string> m_SoundEffects;

	//is weapon on cool down?
	bool m_IsReady;

public:
	Weapon(const std::string weaponName, const std::string damageType, const unsigned int damageValue, const unsigned int hitChance, const unsigned int maxAmmo, const unsigned int cooldownValue, const std::vector<std::string> soundEffects)
	{
		this->m_Name = weaponName;
		this->m_DamageType = damageType;
		this->m_DamageValue = damageValue;
		this->m_HitChance = hitChance;
		this->m_MaxAmmo = maxAmmo;
		this->m_CurrentAmmo = maxAmmo;
		this->m_CooldownValue = cooldownValue;
		for (int i = 0; i < soundEffects.size(); i++)
			this->m_SoundEffects.push_back(soundEffects.at(i));
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

	void playSound(SoundManager& soundManager);
};