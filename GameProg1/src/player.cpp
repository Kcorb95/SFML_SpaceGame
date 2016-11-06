#include <iostream>
#include "stdafx.h"
#include "player.h"

Player::Player()
{
	m_Armor = START_ARMOR;
	m_MaxArmor = START_ARMOR;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;
	m_Damage = START_DAMAGE;

	//Associate a texture with our player sprite
	if (!texturePlayer.loadFromFile("graphics/shipThree.png"))
	{
		std::cerr << "Error loading graphics/shipThree.png" << std::endl;
	}
	spritePlayer.setTexture(texturePlayer);

	//Set the origin of the sprite to the center
	spritePlayer.setOrigin(139.5, 174);
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

void Player::spawn()
{
	//Place the player in the middle of the screen on the left side
	positionPlayer.x = VideoMode::getDesktopMode().width / 7;
	positionPlayer.y = VideoMode::getDesktopMode().height / 2;

	// Strore the resolution for future use
	m_Resolution.x = VideoMode::getDesktopMode().width;
	m_Resolution.y = VideoMode::getDesktopMode().height;
}

FloatRect Player::getPosition()
{
	return spritePlayer.getGlobalBounds();
}

Vector2f Player::getCenter()
{
	return positionPlayer;
}

Sprite Player::getSprite()
{
	return spritePlayer;
}

void Player::update()
{
	spritePlayer.setPosition(positionPlayer);
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

