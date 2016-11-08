#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy
{
private:
	const int START_ARMOR = 100;
	const int START_HEALTH = 100;

	// Where is this enemy located?
	Vector2f m_PositionEnemy;

	// And a texture
	Texture m_TextureEnemy;

	// A sprite for the enemy
	Sprite m_SpriteEnemy;

	// How much health has it got?
	int m_HealthEnemy;

	// How much armor has it got?
	int m_ArmorEnemy;

	// Is it still alive?
	bool m_IsAlive;

public:
	void recieveDamage(int amount);

	// Find out if the zombie is alive
	bool isAlive();

	// Spawn a new zombie
	void spawn(int type);

	// Return a rectangle that is the position in the world
	FloatRect getPosition();

	// Get a copy of the sprite to draw
	Sprite getSprite();

	// How much armor does the Enemy currently have?
	int getArmor();

	// How much health does the Enemy currently have?
	int getHealth();

	// Update the zombie each frame
	void update();
};