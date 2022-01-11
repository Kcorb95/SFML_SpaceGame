#include "Item.h"

ItemType& Item::getItemType()
{
	return this->m_ItemType;
}

std::string Item::getName()
{
	return this->m_Name;
}

int Item::getStrength()
{
	return this->m_Strength;
}

int Item::getDuration()
{
	return this->m_Duration;
}