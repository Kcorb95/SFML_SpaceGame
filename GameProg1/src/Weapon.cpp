#include "Weapon.h"
#include <iostream>

Weapon::Weapon(std::string weaponName, std::string damageType, const unsigned int damageValue, const unsigned int maxAmmo, const unsigned int cooldownValue)
{
	this->m_Name = weaponName;
	this->m_DamageType = damageType;
	this->m_DamageValue = damageValue;
	this->m_MaxAmmo = maxAmmo;
	this->m_CurrentAmmo = maxAmmo;
	this->m_CooldownValue = cooldownValue;
	this->m_IsReady = true;
}

std::string Weapon::getName()
{
	return this->m_Name;
}

std::string Weapon::getDamageType()
{
	return this->m_DamageType;
}

int Weapon::getDamageValue()
{
	return this->m_DamageValue;
}

int Weapon::getMaxAmmo()
{
	return this->m_MaxAmmo;
}

int Weapon::getCurrentAmmo()
{
	return this->m_CurrentAmmo;
}

bool Weapon::isReady()
{
	return this->m_IsReady;
}

void Weapon::decreaseAmmo()
{
	std::cerr <<"Current Ammo: " << m_CurrentAmmo << std::endl;
	--this->m_CurrentAmmo;
	std::cerr << "Current Ammo: " << m_CurrentAmmo << std::endl;
}
