#include <SFML/Graphics.hpp>

#include "AnimationHandler.h"
#include "Ship.h"

void Ship::draw(sf::RenderWindow& window, float dt)
{
	//Change the sprite
	this->m_AnimationHandler.changeAnim(this->shipVariant);

	//update animation
	this->m_AnimationHandler.update(dt);

	//Update the sprite
	this->m_Sprite.setTextureRect(this->m_AnimationHandler.m_Bounds);

	//Draw the ship
	window.draw(this->m_Sprite);

	return;
}

void Ship::update()
{
	return;
}

int Ship::getCurrentArmor()
{
	return this->m_Armor;
}

int Ship::getMaxArmor()
{
	return this->m_MaxArmor;
}


int Ship::getCurrentHealth()
{
	return this->m_Health;
}

int Ship::getMaxHealth()
{
	return this->m_MaxHealth;
}

Weapon Ship::getWeapon(int index)
{
	if (index < m_Weapons.size())
		return m_Weapons.at(index);
	else
		return m_Weapons.at(0);
}

void Ship::setPosition(Vector2f position)
{
	this->m_Sprite.setPosition(position);
}

void Ship::setRotation(int degrees)
{
	this->m_Sprite.setRotation(degrees);
}
