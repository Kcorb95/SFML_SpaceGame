#include "stdafx.h"
#include "Enemy.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;


void Enemy::spawn(int type)
{

	switch (type)
	{
	case 0:
		// Small Enemy
		//Associate a texture with our player sprite
		if (!textureEnemy.loadFromFile("graphics/shipThree.png"))
		{
			std::cerr << "Error loading graphics/shipThree.png" << std::endl;
		}
		spriteEnemy.setTexture(textureEnemy);

		armorEnemy = 100;
		healthEnemy = 100;
		break;

	case 1:
		// Medium Enemy
		//Associate a texture with our player sprite
		if (!textureEnemy.loadFromFile("graphics/shipThree.png"))
		{
			std::cerr << "Error loading graphics/shipThree.png" << std::endl;
		}
		spriteEnemy.setTexture(textureEnemy);

		armorEnemy = 150;
		healthEnemy = 150;
		break;

	case 2:
		// Large Enemy
		//Associate a texture with our player sprite
		if (!textureEnemy.loadFromFile("graphics/shipThree.png"))
		{
			std::cerr << "Error loading graphics/shipThree.png" << std::endl;
		}
		spriteEnemy.setTexture(textureEnemy);

		armorEnemy = 200;
		healthEnemy = 200;
		break;
	}

	positionEnemy.x = VideoMode::getDesktopMode().width / 1.135;
	positionEnemy.y = VideoMode::getDesktopMode().height / 2;

	spriteEnemy.setOrigin(139.5, 174);
	spriteEnemy.setRotation(180);
	spriteEnemy.setPosition(positionEnemy);
}

bool Enemy::isAlive()
{
	return enemyIsAlive;
}

FloatRect Enemy::getPosition()
{
	return spriteEnemy.getGlobalBounds();
}


Sprite Enemy::getSprite()
{
	return spriteEnemy;
}

int Enemy::getArmor()
{
	return armorEnemy;
}

int Enemy::getHealth()
{
	return healthEnemy;
}

void Enemy::update()
{
	// Move the sprite
	spriteEnemy.setPosition(positionEnemy);
}