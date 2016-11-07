#include "stdafx.h"
#include "Weapon.h"

Weapon::Weapon(String weaponName, String damageType, int damageValue, int startingAmmo, int currentAmmo, int cooldownValue)
{
	m_Name = weaponName;
	m_DamageType = damageType;
	m_DamageValue = damageValue;
	m_StartingAmmo = startingAmmo;
	m_CurrentAmmo = currentAmmo;
	m_CooldownValue = cooldownValue;
	m_IsReady = true;
}

String Weapon::getName()
{
	return m_Name;
}

String Weapon::getDamageType() 
{
	return m_DamageType;
}

int Weapon::getDamageValue()
{
	return m_DamageValue;
}

int Weapon::getStartingAmmo()
{
	return m_StartingAmmo;
}

int Weapon::getCurrentAmmo()
{
	return m_CurrentAmmo;
}

bool Weapon::isReady()
{
	return m_IsReady;
}