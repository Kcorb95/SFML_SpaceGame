#include "GUI.h"

sf::Vector2f GUI::getSize()
{
	return sf::Vector2f(this->m_Dimensions.x, this->m_Dimensions.y * this->m_Entries.size());
}

int GUI::getEntry(const sf::Vector2f mousePos)
{
	//If there are no entries then outside the menu
	if (m_Entries.size() == 0)
		return -1;
	if (!this->m_Visible)
		return -1;
	for (int i = 0; i < this->m_Entries.size(); ++i)
	{
		/* Translate point to use the entry's local coordinates. */
		sf::Vector2f point = mousePos;
		point += this->m_Entries[i].m_Shape.getOrigin();
		point -= this->m_Entries[i].m_Shape.getPosition();

		if (point.x < 0 || point.x > this->m_Entries[i].m_Shape.getScale().x * this->m_Dimensions.x) continue;
		if (point.y < 0 || point.y > this->m_Entries[i].m_Shape.getScale().y * this->m_Dimensions.y) continue;
		return i;
	}
	return -1;
}

void GUI::setEntryText(int entry, std::string text)
{
	if (entry >= m_Entries.size() || entry < 0)
		return;

	m_Entries[entry].m_Text.setString(text);

	return;
}

void GUI::setDimensions(sf::Vector2f dimensions)
{
	this->m_Dimensions = dimensions;

	for (auto& entry : m_Entries)
	{
		entry.m_Shape.setSize(dimensions);
		entry.m_Text.setCharacterSize(dimensions.y - m_Style.m_BorderSize - m_Padding);
	}
	return;
}

void GUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!m_Visible)
		return;

	/* Draw each entry of the menu */
	for (auto entry : this->m_Entries)
	{
		/* Draw the entry */
		target.draw(entry.m_Shape);
		target.draw(entry.m_Text);
	}
	return;
}

void GUI::show()
{
	sf::Vector2f offset(0.0f, 0.0f);

	this->m_Visible = true;

	//Draw each entry of the menu
	for (auto& entry : this->m_Entries)
	{
		//Set the origin of the entry
		sf::Vector2f origin = this->getOrigin();
		origin -= offset;
		entry.m_Shape.setOrigin(origin);
		entry.m_Text.setOrigin(origin);

		//Compute the position of the entry
		entry.m_Shape.setPosition(this->getPosition());
		entry.m_Text.setPosition(this->getPosition());

		if (this->m_Horizontal)
			offset.x += this->m_Dimensions.x;
		else
			offset.y += this->m_Dimensions.y;
	}
	return;
}

void GUI::hide()
{
	this->m_Visible = false;
	return;
}

void GUI::highlight(const int entry)
{
	for (int i = 0; i < m_Entries.size(); ++i) {
		if (i == entry)
		{
			m_Entries[i].m_Shape.setFillColor(m_Style.m_BodyHighlightCol);
			m_Entries[i].m_Shape.setOutlineColor(m_Style.m_BorderHighlightCol);
			m_Entries[i].m_Text.setFillColor(m_Style.m_TextHighlightCol);
		}
		else
		{
			m_Entries[i].m_Shape.setFillColor(m_Style.m_BodyCol);
			m_Entries[i].m_Shape.setOutlineColor(m_Style.m_BorderCol);
			m_Entries[i].m_Text.setFillColor(m_Style.m_TextCol);
		}
	}
	return;
}

std::string GUI::activate(const int entry)
{
	if (entry == -1)
		return "null";
	return m_Entries[entry].m_Message;
}

std::string GUI::activate(const sf::Vector2f mousePos)
{
	int entry = this->getEntry(mousePos);
	return this->activate(entry);
}