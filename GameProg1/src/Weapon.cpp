#include "Weapon.h"

Weapon::Weapon(std::string weaponName, std::string damageType, int damageValue, int maxAmmo, int currentAmmo, int cooldownValue)
{
	m_Name = weaponName;
	m_DamageType = damageType;
	m_DamageValue = damageValue;
	m_MaxAmmo = maxAmmo;
	m_CurrentAmmo = currentAmmo;
	m_CooldownValue = cooldownValue;
	m_IsReady = true;
}

std::string Weapon::getName()
{
	return m_Name;
}

std::string Weapon::getDamageType()
{
	return m_DamageType;
}

int Weapon::getDamageValue()
{
	return m_DamageValue;
}

int Weapon::getMaxAmmo()
{
	return m_MaxAmmo;
}

int Weapon::getCurrentAmmo()
{
	return m_CurrentAmmo;
}

bool Weapon::isReady()
{
	return m_IsReady;
}

void Weapon::decreaseAmmo()
{
	--m_CurrentAmmo;
}
