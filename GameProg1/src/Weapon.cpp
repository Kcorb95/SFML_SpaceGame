#include "Weapon.h"
#include <iostream>

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
	std::cerr << "Current Ammo: " << m_CurrentAmmo << std::endl;
	--this->m_CurrentAmmo;
	std::cerr << "Current Ammo: " << m_CurrentAmmo << std::endl;
}

void Weapon::increaseAmmo(int amount)
{
	this->m_CurrentAmmo += amount;
}
