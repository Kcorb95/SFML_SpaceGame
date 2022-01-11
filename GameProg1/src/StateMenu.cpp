#include <SFML/Graphics.hpp>

#include "StateMenu.h"
#include "StateGame.h"
#include "State.h"
#include <iostream>

void StateMenu::draw(const float dt)
{
	this->m_Game->m_Window.setView(this->m_View);

	this->m_Game->m_Window.clear(sf::Color::Black);
	this->m_Game->m_Window.draw(this->m_Game->m_Background);

	for (auto gui : this->m_GUISystem)
		this->m_Game->m_Window.draw(gui.second);

	return;
}

void StateMenu::update(const float dt)
{
}

void StateMenu::input()
{
	sf::Event event;

	sf::Vector2f mousePos = this->m_Game->m_Window.mapPixelToCoords(sf::Mouse::getPosition(this->m_Game->m_Window), this->m_View);

	while (this->m_Game->m_Window.pollEvent(event))
	{
		switch (event.type)
		{
			//Close the window
		case sf::Event::Closed:
			{
				m_Game->m_Window.close();
			}
			//Resize the window
		case sf::Event::Resized:
			{
				this->m_View.setSize(event.size.width, event.size.height);
				this->m_Game->m_Background.setPosition(this->m_Game->m_Window.mapPixelToCoords(sf::Vector2i(0, 0), this->m_View));
				sf::Vector2f pos = sf::Vector2f(event.size.width, event.size.height);
				pos *= 0.5f;
				pos = this->m_Game->m_Window.mapPixelToCoords(sf::Vector2i(pos), this->m_View);
				this->m_GUISystem.at("menu").setPosition(pos);
				this->m_Game->m_Background.setScale(
					    float(event.size.width) / float(this->m_Game->m_Background.getTexture()->getSize().x),
					    float(event.size.height) / float(this->m_Game->m_Background.getTexture()->getSize().y));
				break;
			}
			//Highlight Menu Items
		case sf::Event::MouseMoved:
			{
				this->m_GUISystem.at("menu").highlight(this->m_GUISystem.at("menu").getEntry(mousePos));
				break;;
			}

			//Click on Menu Items
		case sf::Event::MouseButtonPressed:
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::string msg = this->m_GUISystem.at("menu").activate(mousePos);

					if (msg == "new_game")
					{
						this->loadGame();
					}
					else if (msg == "exit_game")
					{
						m_Game->m_Window.close();
					}
					else if (msg == "continue_game")
					{
						this->m_Game->m_MenuMusic.stop();
						this->m_Game->m_GameMusic.play();
						m_Game->m_States.pop();
					}
				}
				break;
			}
			//Handle key presses
		case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Escape)
					this->m_Game->m_Window.close();
				break;
			}
		default:
			break;
		}
	}
	return;
}

void StateMenu::loadGame()
{
	this->m_Game->pushState(new StateGame(this->m_Game));
	return;
}

StateMenu::StateMenu(Game* game)
{
	this->m_Game = game;
	sf::Vector2f pos = sf::Vector2f(this->m_Game->m_Window.getSize());
	this->m_View.setSize(pos);
	pos *= 0.5f;
	this->m_View.setCenter(pos);

	std::vector<std::pair<std::string, std::string>> menu;
	if (m_Game->m_States.size() > 1)
		menu.push_back(std::make_pair("Continue", "continue_game"));
	else
		menu.push_back(std::make_pair("New Game", "new_game"));
	menu.push_back(std::make_pair("Exit Game", "exit_game"));

	this->m_GUISystem.emplace("menu", GUI(sf::Vector2f(525, 100), 2, false, m_Game->m_StyleSheets.at("menu"), menu));

	this->m_GUISystem.at("menu").setOrigin(this->m_GUISystem.at("menu").getSize().x * 0.5f, this->m_GUISystem.at("menu").getSize().y * 0.5f);
	this->m_GUISystem.at("menu").setPosition(pos);
	this->m_GUISystem.at("menu").show();

	this->m_Game->m_GameMusic.stop();
	this->m_Game->m_MenuMusic.play();
}