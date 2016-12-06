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

	int m_Structure;
	int m_MaxStructure;

public:
	AnimationHandler m_AnimationHandler;
	sf::Sprite m_Sprite;

	std::vector<Weapon> m_Weapons;

	//Allows different looking versions of the same ship
	int shipVariant = 0;

	bool isAlive = true;

	Ship() {}

	Ship(const unsigned int maxArmor, const unsigned int maxStructure, const std::vector<Weapon>& weapons,
		const Vector2f shipDimensions, const sf::Texture& texture, const std::vector<Animation>& animations)
	{
		this->m_Armor = maxArmor;
		this->m_MaxArmor = maxArmor;

		this->m_Structure = maxStructure;
		this->m_MaxStructure = maxStructure;

		for (int i = 0; i < weapons.size(); i++)
			this->m_Weapons.push_back(weapons.at(i));

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

	int getCurrentStructure();
	int getMaxStructure();

	Weapon getWeapon(int index);

	void setPosition(Vector2f position);

	void setRotation(int degrees);

	void repair(int amount, int location);

	void damage(Weapon weapon);

	void damage(int amount, int location);

	void damageArmor(int amount);
	
	void damageStructure(int amount);
};