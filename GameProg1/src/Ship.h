#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "AnimationHandler.h"
#include "Weapon.h"

class Ship
{
private:
	int m_Armor;
	int m_MaxArmor;

	int m_Health;
	int m_MaxHealth;

	std::vector<Weapon> m_Weapons;

public:
	AnimationHandler m_AnimationHandler;
	sf::Sprite m_Sprite;

	//Allows different looking versions of the same ship
	int shipVariant = 0;

	Ship() {}

	Ship(const unsigned int maxArmor, const unsigned int maxHealth, const std::vector<Weapon>& weapons,
		Vector2f shipDimensions, sf::Texture& texture, const std::vector<Animation>& animations)
	{
		this->m_Armor = maxArmor;
		this->m_MaxArmor = maxArmor;

		this->m_Health = maxHealth;
		this->m_MaxHealth = maxHealth;

		this->m_Sprite.setOrigin(sf::Vector2f(0.0f, shipDimensions.y * 0.5f));
		this->m_Sprite.setTexture(texture);
		this->m_AnimationHandler.m_FrameSize = sf::IntRect(0, 0, shipDimensions.x, shipDimensions.y);
		for (auto animation : animations)
		{
			this->m_AnimationHandler.addAnim(animation);
		}
		this->m_AnimationHandler.update(0.0f);
	}

	void draw(sf::RenderWindow& window, float dt);

	void update();

	int getCurrentArmor();
	int getMaxArmor();

	int getCurrentHealth();
	int getMaxHealth();

	Weapon getWeapon(int index);

	void setPosition(Vector2f position);

	void setRotation(int degrees);
};