#include "Enemy.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

void Enemy::spawn(int type, Vector2f position)
{

	switch (type)
	{
	case 0:
		// Small Enemy
		//Associate a texture with our player sprite
		if (!m_TextureEnemy.loadFromFile("graphics/shipThree.png"))
		{
			std::cerr << "Error loading graphics/shipThree.png" << std::endl;
		}
		m_SpriteEnemy.setTexture(m_TextureEnemy);

		m_ArmorEnemy = 100;
		m_HealthEnemy = 100;
		break;

	case 1:
		// Medium Enemy
		//Associate a texture with our player sprite
		if (!m_TextureEnemy.loadFromFile("graphics/shipThree.png"))
		{
			std::cerr << "Error loading graphics/shipThree.png" << std::endl;
		}
		m_SpriteEnemy.setTexture(m_TextureEnemy);

		m_ArmorEnemy = 150;
		m_HealthEnemy = 150;
		break;

	case 2:
		// Large Enemy
		//Associate a texture with our player sprite
		if (!m_TextureEnemy.loadFromFile("graphics/shipThree.png"))
		{
			std::cerr << "Error loading graphics/shipThree.png" << std::endl;
		}
		m_SpriteEnemy.setTexture(m_TextureEnemy);

		m_ArmorEnemy = 200;
		m_HealthEnemy = 200;
		break;
	}

	m_PositionEnemy.x = position.x;
	m_PositionEnemy.y = position.y;

	m_SpriteEnemy.setOrigin(0, m_TextureEnemy.getSize().y * 0.5f);

	m_SpriteEnemy.setRotation(180);
	m_SpriteEnemy.setPosition(m_PositionEnemy);
}

void Enemy::recieveDamage(int amount)
{
	m_HealthEnemy -= amount;
}

bool Enemy::isAlive()
{
	return m_IsAlive;
}

FloatRect Enemy::getPosition()
{
	return m_SpriteEnemy.getGlobalBounds();
}


Sprite Enemy::getSprite()
{
	return m_SpriteEnemy;
}

int Enemy::getArmor()
{
	return m_ArmorEnemy;
}

int Enemy::getHealth()
{
	return m_HealthEnemy;
}

void Enemy::update()
{
	// Move the sprite
	m_SpriteEnemy.setPosition(m_PositionEnemy);
}