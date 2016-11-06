#include "stdafx.h"
#include "player.h"
#include "TextureHolder.h"

Player::Player()
{
	m_Armor = START_ARMOR;
	m_MaxArmor = START_ARMOR;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;
	m_Damage = START_DAMAGE;

	//Associate a texture with our player sprite
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/shipThree.png"));

	//Set the origin of the sprite to the center
	m_Sprite.setOrigin(25, 25);
}

void Player::resetPlayerStats()
{
	m_Armor = START_ARMOR;
	m_MaxArmor = START_ARMOR;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;
	m_Damage = START_DAMAGE;
	m_MaxDamage = START_DAMAGE;

}

void Player::spawn(IntRect space, Vector2f resolution)
{
	//Place the player in the middle of the screen on the left side
	m_Position.x = space.width / 2;
	m_Position.y = space.height / 2;

	// Strore the resolution for future use
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;
}

FloatRect Player::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f Player::getCenter()
{
	return m_Position;
}

Sprite Player::getSprite()
{
	return m_Sprite;
}

int Player::getArmor()
{
	return m_Armor;
}

int Player::getHealth()
{
	return m_Health;
}

int Player::getDamage()
{
	return m_Damage;
}

void Player::upgradeArmor()
{
	// Increase max Armor by 10 points
	m_MaxArmor += (START_ARMOR + 10);
}

void Player::upgradeHealth()
{
	// Increase max Health by 10 points
	m_MaxHealth += (START_HEALTH + 10);
}

void Player::upgradeDamage()
{
	// Increase damage per attack by 1
	m_MaxDamage += (START_DAMAGE + 1);
}

void Player::increaseArmorLevel(int amount)
{
	m_Armor += amount;

	// But not beyond the maximum
	if (m_Armor > m_MaxArmor)
	{
		m_Armor = m_MaxArmor;
	}
}

void Player::increaseHealthLevel(int amount)
{
	m_Health += amount;

	// But not beyond the maximum
	if (m_Health > m_MaxHealth)
	{
		m_Health = m_MaxHealth;
	}
}

void Player::increaseDamageAmount(int amount)
{
	m_Damage += amount;

	// But not beyond the maximum
	if (m_Damage > m_MaxDamage)
	{
		m_Damage = m_MaxDamage;
	}
}

