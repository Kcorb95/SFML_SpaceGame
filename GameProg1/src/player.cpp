#include <iostream>
#include "stdafx.h"
#include "player.h"

Player::Player()
{
	armorPlayer = START_ARMOR;
	maxArmorPlayer = START_ARMOR;
	healthPlayer = START_HEALTH;
	maxHealthPlayer = START_HEALTH;
	damagePlayer = START_DAMAGE;

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
	armorPlayer = START_ARMOR;
	maxArmorPlayer = START_ARMOR;
	healthPlayer = START_HEALTH;
	maxHealthPlayer = START_HEALTH;
	damagePlayer = START_DAMAGE;
	maxDamagePlayer = START_DAMAGE;
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
	return armorPlayer;
}

int Player::getHealth()
{
	return healthPlayer;
}

int Player::getDamage()
{
	return damagePlayer;
}

void Player::upgradeArmor()
{
	// Increase max Armor by 10 points
	maxArmorPlayer += (START_ARMOR + 10);
}

void Player::upgradeHealth()
{
	// Increase max Health by 10 points
	maxHealthPlayer += (START_HEALTH + 10);
}

void Player::upgradeDamage()
{
	// Increase damage per attack by 1
	maxDamagePlayer += (START_DAMAGE + 1);
}

void Player::increaseArmorLevel(int amount)
{
	armorPlayer += amount;

	// But not beyond the maximum
	if (armorPlayer > maxArmorPlayer)
	{
		armorPlayer = maxArmorPlayer;
	}
}

void Player::increaseHealthLevel(int amount)
{
	healthPlayer += amount;

	// But not beyond the maximum
	if (healthPlayer > maxHealthPlayer)
	{
		healthPlayer = maxHealthPlayer;
	}
}

void Player::increaseDamageAmount(int amount)
{
	damagePlayer += amount;

	// But not beyond the maximum
	if (damagePlayer > maxDamagePlayer)
	{
		damagePlayer = maxDamagePlayer;
	}
}

