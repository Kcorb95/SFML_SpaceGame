#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "AnimationHandler.h"
#include "Weapon.h"
#include "Item.h"

class Ship
{
private:
	//Current and Maximum Armor
	int m_Armor;
	int m_MaxArmor;

	//Current and Maximum Structure
	int m_Structure;
	int m_MaxStructure;

	//Current and Maximum Evasion
	int m_Evasion;
	int m_MaxEvasion;

public:
	AnimationHandler m_AnimationHandler;
	sf::Sprite m_Sprite;

	//Vector of available weapons
	std::vector<Weapon> m_Weapons;

	//Vector of available items
	std::vector<Item> m_Items;

	//Vector of Item pairs that the ship has available
	std::vector<std::pair<std::string, std::string>> m_ItemPairs;

	//Allows different looking versions of the same ship
	int shipVariant = 0;

	//Is the ship still above 0 structure?
	bool isAlive = true;
	
	//is the ships evasion currently boosted?
	bool m_IsBoosted = false;

	Ship() { }

	Ship(const unsigned int maxArmor, const unsigned int maxStructure, int evasion, const std::vector<Weapon>& weapons, const std::vector<Item>& items,
		const sf::Vector2f shipDimensions, const sf::Texture& texture, const std::vector<Animation>& animations)
	{
		this->m_Armor = maxArmor;
		this->m_MaxArmor = maxArmor;

		this->m_Structure = maxStructure;
		this->m_MaxStructure = maxStructure;

		this->m_Evasion = evasion;
		this->m_MaxEvasion = evasion;

		for (int i = 0; i < weapons.size(); i++)
			this->m_Weapons.push_back(weapons.at(i));

		for (int i = 0; i < items.size(); i++)
			this->m_Items.push_back(items.at(i));

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

	Weapon& getWeapon(int index);

	Item& getItem(int index);

	void useItem(Item item);

	void setPosition(sf::Vector2f position);

	void setRotation(int degrees);

	void repair(int amount, int location);

	void increaseEvasion(bool isBoosted, int strength);

	int getEvasion();

	void damage(Weapon weapon);

	void damage(int amount, int location);

	void damageArmor(int amount);

	void damageStructure(int amount);
};
