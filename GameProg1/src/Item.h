#pragma once
#include <SFML/Graphics.hpp>

//Item type
enum class ItemType { ShieldBoost, EvasionBoost, ArmorRepair, StructureRepair };

class Item
{
private:
	//Item Type
	ItemType m_ItemType;

	//Item Name
	std::string m_Name;

	//How strong the item is
	int m_Strength;

	//Duration of item in turns
	int m_Duration;

public:
	Item() {}

	Item(const ItemType itemType, const std::string itemName, const unsigned int strength, const unsigned int duration)
	{
		this->m_ItemType = itemType;
		this->m_Name = itemName;
		this->m_Strength = strength;
		this->m_Duration = duration;
	}

	ItemType& getItemType();
	std::string getName();
	int getStrength();
	int getDuration();
};