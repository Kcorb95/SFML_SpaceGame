#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Weapon.h"

using namespace sf;

class Player
{
private:
	const int START_ARMOR = 100;
	const int START_HEALTH = 100;
	const int START_DAMAGE = 10;

	bool m_IsAlive = true;

	// Where is the player
	Vector2f m_PositionPlayer;

	// Of course we will need a sprite
	Sprite m_SpritePlayer;

	// And a texture
	Texture m_TexturePlayer;

	// What is the screen resolution
	Vector2f m_Resolution;

	// How much armor has the player got?
	int m_ArmorPlayer;
	// What is the maximum armor the player can have
	int m_MaxArmorPlayer;

	// How much health has the player got?
	int m_HealthPlayer;
	// What is the maximum health the player can have
	int m_MaxHealthPlayer;

	// How much damage can the player do per attack?
	int m_DamagePlayer;
	//What is the maximum amount of damage a player can do
	int m_MaxDamagePlayer;

public:
	Player();

	std::vector<Weapon> m_Weapons;

	bool isAlive();

	// Call this at the end of every game
	void resetPlayerStats();

	void spawn();

	void recieveDamage(int amount);//can maybe make this return bool for alive not alive state or even the int for the remaining health

	// Where is the player
	FloatRect getPosition();

	// Where is the center of the player
	Vector2f getCenter();

	// Send a copy of the sprite to main
	Sprite getSprite();

	Weapon getWeapon(int index);

	int getCurrentWeapons();

	// How much armor has the player currently got?
	int getArmor();

	// How much health has the player currently got?
	int getHealth();

	//Called once every frame to update player
	void update();

	// Give the player some armor
	void upgradeArmor();

	// Give the player some health
	void upgradeHealth();

	// Increase the maximum amount of armor the player can have
	void increaseArmorLevel(int amount);

	// Increase the maximum amount of health the player can have
	void increaseHealthLevel(int amount);

	// Increase the maximum amount of damage the player can do
	void increaseDamageAmount(int amount);
};