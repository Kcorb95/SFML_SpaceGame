#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>

class GUIStyle
{
public:
	sf::Color m_BodyCol;
	sf::Color m_BodyHighlightCol;
	sf::Color m_BorderCol;
	sf::Color m_BorderHighlightCol;
	sf::Color m_TextCol;
	sf::Color m_TextHighlightCol;
	sf::Font* m_Font;

	float m_BorderSize;

	GUIStyle(sf::Font* font, float borderSize,
		sf::Color bodyCol, sf::Color borderCol, sf::Color textCol,
		sf::Color bodyHighlightCol, sf::Color borderHighlightCol, sf::Color textHighlightCol)
	{
		this->m_BodyCol = bodyCol;
		this->m_BorderCol = borderCol;
		this->m_TextCol = textCol;
		this->m_BodyHighlightCol = bodyHighlightCol;
		this->m_BorderHighlightCol = borderHighlightCol;
		this->m_TextHighlightCol = textHighlightCol;
		this->m_Font = font;
		this->m_BorderSize = borderSize;
	}
	GUIStyle() {}
};

class GUIEntry
{
public:
	//Handles appearance of the entry
	sf::RectangleShape m_Shape;

	//String returned when the entry is activated
	std::string m_Message;

	//Text displayed on the entry
	sf::Text m_Text;

	GUIEntry(const std::string& message, sf::RectangleShape shape, sf::Text text)
	{
		this->m_Message = message;
		this->m_Shape = shape;
		this->m_Text = text;
	}
	GUIEntry() {}
};

class GUI : public sf::Transformable, public sf::Drawable
{
private:
	//If true the menu entries will be horizontally, not vertically adjacent
	bool m_Horizontal;

	GUIStyle m_Style;

	sf::Vector2f m_Dimensions;

	int m_Padding;

public:
	std::vector<GUIEntry> m_Entries;

	bool m_Visible;

	//Constructor
	GUI(sf::Vector2f dimensions, int padding, bool horizontal,
		GUIStyle& style, std::vector<std::pair<std::string, std::string>> entries)
	{
		m_Visible = false;
		this->m_Horizontal = horizontal;
		this->m_Style = style;
		this->m_Dimensions = dimensions;
		this->m_Padding = padding;

		// Construct the background shape
		sf::RectangleShape shape;
		shape.setSize(dimensions);
		shape.setFillColor(style.m_BodyCol);
		shape.setOutlineThickness(-style.m_BorderSize);
		shape.setOutlineColor(style.m_BorderCol);

		//Construct each GUI entry
		for (auto entry : entries)
		{
			//Construct the Text
			sf::Text text;
			text.setString(entry.first);
			text.setFont(*style.m_Font);
			text.setFillColor(style.m_TextCol);
			text.setCharacterSize(dimensions.y - style.m_BorderSize - padding);

			this->m_Entries.push_back(GUIEntry(entry.second, shape, text));
		}
	}

	sf::Vector2f getSize();

	//Return the entry that the mouse is hovering over. Returns -1 if the mouse is outside of the GUI
	int getEntry(const sf::Vector2f mousePos);

	//Change the text of an entry
	void setEntryText(int entry, std::string text);

	//Change the entry dimensions
	void setDimensions(sf::Vector2f dimensions);

	//Draw the menu
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void show();

	void hide();

	//Highlights an entry of the menu
	void highlight(const int entry);

	//Return the message bound to the entry
	std::string activate(const int entry);
	std::string activate(const sf::Vector2f mousePos);
};