#include "Weapon.h"

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

int Weapon::getHitChance()
{
	return this->m_HitChance;
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
	--this->m_CurrentAmmo;
}

void Weapon::increaseAmmo(int amount)
{
	this->m_CurrentAmmo += amount;
}

void Weapon::playSound(SoundManager& soundManager)
{
	srand(time(NULL));
	int r = rand() % (this->m_SoundEffects.size() - 0) + 0;

	soundManager.getRef(this->m_SoundEffects.at(r)).play();
}