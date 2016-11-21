#include <iostream>
#include "Player.h"

Player::Player()
{
	m_ArmorPlayer = START_ARMOR;
	m_MaxArmorPlayer = START_ARMOR;
	m_HealthPlayer = START_HEALTH;
	m_MaxHealthPlayer = START_HEALTH;
	m_DamagePlayer = START_DAMAGE;
	Weapon basicRail = Weapon("Basic Railgun", "Kinetic", 5, 50, 50, 0);
	Weapon basicMissile = Weapon("Basic Missile Launcher", "Ballistic", 10, 5, 5, 2);

	m_Weapons.push_back(basicRail);
	m_Weapons.push_back(basicMissile);

	//Associate a texture with our player sprite
	if (!m_TexturePlayer.loadFromFile("graphics/shipThree.png"))
	{
		std::cerr << "Error loading graphics/shipThree.png" << std::endl;
	}
	m_SpritePlayer.setTexture(m_TexturePlayer);

	//Set the origin of the sprite to the center
	m_SpritePlayer.setOrigin(0, m_TexturePlayer.getSize().y * 0.5f);
}

void Player::recieveDamage(int amount)
{
	if (amount <= m_HealthPlayer)
	{
		m_HealthPlayer -= amount;
	}
	else
	{
		m_IsAlive = false;
	}
}

bool Player::isAlive()
{
	return m_IsAlive;
}

Weapon Player::getWeapon(int index)
{
	if (index < m_Weapons.size())
		return m_Weapons.at(index);
	else
		return m_Weapons.at(0);
}

int Player::getCurrentWeapons()
{
	return m_Weapons.size();
}

void Player::resetPlayerStats()
{
	m_ArmorPlayer = START_ARMOR;
	m_MaxArmorPlayer = START_ARMOR;
	m_HealthPlayer = START_HEALTH;
	m_MaxHealthPlayer = START_HEALTH;
	m_DamagePlayer = START_DAMAGE;
	m_MaxDamagePlayer = START_DAMAGE;
}

void Player::spawn(Vector2f position)
{
	//Place the player in the middle of the screen on the left side
	m_PositionPlayer.x = position.x;
	m_PositionPlayer.y = position.y;

	// Store the resolution for future use
	m_Resolution.x = position.x;
	m_Resolution.y = position.y;
}

FloatRect Player::getPosition()
{
	return m_SpritePlayer.getGlobalBounds();
}

Vector2f Player::getCenter()
{
	return m_PositionPlayer;
}

Sprite Player::getSprite()
{
	return m_SpritePlayer;
}

void Player::update()
{
	m_SpritePlayer.setPosition(m_PositionPlayer);
}

int Player::getArmor()
{
	return m_ArmorPlayer;
}

int Player::getHealth()
{
	return m_HealthPlayer;
}

void Player::upgradeArmor()
{
	// Increase max Armor by 10 points
	m_MaxArmorPlayer += (START_ARMOR + 10);
}

void Player::upgradeHealth()
{
	// Increase max Health by 10 points
	m_MaxHealthPlayer += (START_HEALTH + 10);
}

void Player::increaseArmorLevel(int amount)
{
	m_ArmorPlayer += amount;

	// But not beyond the maximum
	if (m_ArmorPlayer > m_MaxArmorPlayer)
	{
		m_ArmorPlayer = m_MaxArmorPlayer;
	}
}

void Player::increaseHealthLevel(int amount)
{
	m_HealthPlayer += amount;

	// But not beyond the maximum
	if (m_HealthPlayer > m_MaxHealthPlayer)
	{
		m_HealthPlayer = m_MaxHealthPlayer;
	}
}

void Player::increaseDamageAmount(int amount)
{
	m_DamagePlayer += amount;

	// But not beyond the maximum
	if (m_DamagePlayer > m_MaxDamagePlayer)
	{
		m_DamagePlayer = m_MaxDamagePlayer;
	}
}