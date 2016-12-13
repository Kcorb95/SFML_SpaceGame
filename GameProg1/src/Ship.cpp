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

int Ship::getCurrentStructure()
{
	return this->m_Structure;
}

int Ship::getMaxStructure()
{
	return this->m_MaxStructure;
}

Weapon& Ship::getWeapon(int index)
{
	if (index < this->m_Weapons.size())
		return this->m_Weapons.at(index);
	else
		return this->m_Weapons.at(0);
}

Item& Ship::getItem(int index)
{
	if (index < this->m_Items.size())
		return this->m_Items.at(index);
	else
		return this->m_Items.at(0);
}

void Ship::setPosition(sf::Vector2f position)
{
	this->m_Sprite.setPosition(position);
}

void Ship::setRotation(int degrees)
{
	this->m_Sprite.setRotation(degrees);
}

void Ship::repair(int amount, int type)
{
	if (type == 1)
		this->m_Structure += amount;
	else
		this->m_Armor += amount;
}

void Ship::increaseEvasion(bool isBoosted, int strength)
{
	if (isBoosted)
		this->m_Evasion += strength;
	else
		this->m_Evasion == this->m_MaxEvasion;
}

int Ship::getEvasion()
{
	return this->m_Evasion;
}


void Ship::damage(Weapon weapon)
{
	std::string damageType = weapon.getDamageType();
	if (damageType == "Kinetic")
		damage(weapon.getDamageValue(), 1);
	else if (damageType == "Ballistic")
		damage(weapon.getDamageValue(), 2);
}

/*0 For Shield
 *1 For Armor
 *2 For Structure
 */
void Ship::damage(int amount, int location)
{
	switch (location)
	{
	case 1: //Kinetic good against Armor, bad against else
		damageArmor(amount);
		break;
	case 2: //Ballistic good against Structure, bad against else
		if (this->m_Armor == 0)//if there is no Armor
			damageStructure(amount); //damage structure for normal amount
		else//then there is Armor
		{
			if ((amount / 2) > this->m_Armor)//If I will do more reduced damage than there is remaining armor
			{
				amount /= 2;// set the amount to half
				amount -= this->m_Armor;//"deal" the damage
				this->m_Armor = 0; //"deal" the damage
				damageStructure(amount * 2);//deal the remaining normal damage to structure
			}
			else
				damageArmor(amount / 2);//deal reduced damage to Armor
		}
		break;
	}
}

void Ship::damageArmor(int amount)
{
	if (this->m_Armor == 0)//If no remaining Armor
		damageStructure(amount / 2);//Deal reduced damage to structure
	else if (amount > this->m_Armor)//if you deal more damage than there is remaining armor
	{
		amount -= this->m_Armor;//reduce the amount of damage by the remaining armor
		this->m_Armor = 0;//set armor to zero since you just "dealt" that damage
		damageStructure(amount / 2);//deal the reduced remaining damage
	}
	else//damage Armor for normal amount
		this->m_Armor -= amount;
}

void Ship::damageStructure(int amount)
{
	if (amount < this->m_Structure)//if the amount of damage to be dealt *wont* kill the target
	{
		this->m_Structure -= amount;
	}
	else //target is totally dead
	{
		this->isAlive = false;
		this->m_Structure = 0;
	}
}

void Ship::useItem(Item item)
{
	if (item.getItemType() == ItemType::ArmorRepair)
		repair(item.getStrength(), 2);
	else if (item.getItemType() == ItemType::StructureRepair)
		repair(item.getStrength(), 1);
	else if (item.getItemType() == ItemType::ShieldBoost)
		repair(item.getStrength(), 3);
	else if (item.getItemType() == ItemType::EvasionBoost)
		increaseEvasion(m_IsBoosted, item.getStrength());
}