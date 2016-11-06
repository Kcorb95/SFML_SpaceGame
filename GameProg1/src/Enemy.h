#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

class Enemy
{
private:
	const int START_ARMOR = 100;
	const int START_HEALTH = 100;

	// Where is this enemy located?
	Vector2f positionEnemy;

	// And a texture
	Texture textureEnemy;

	// A sprite for the enemy
	Sprite spriteEnemy;

	// How much health has it got?
	int healthEnemy;

	// How much armor has it got?
	int armorEnemy;

	// Is it still alive?
	bool enemyIsAlive;

public:
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