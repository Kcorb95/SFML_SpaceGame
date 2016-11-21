#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Game.h"
#include "State.h"
#include "TextureManager.h"

void Game::pushState(State* state)
{
	this->m_States.push(state);
	return;
}

void Game::popState()
{
	delete this->m_States.top();
	this->m_States.pop();
	return;
}

void Game::changeState(State* state)
{
	if (!this->m_States.empty())
		popState();
	pushState(state);
	return;
}

State* Game::peekState()
{
	if (this->m_States.empty())
		return nullptr;
	return this->m_States.top();
}

void Game::gameLoop()
{
	sf::Clock clock;

	while (this->m_Window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		if (peekState() == nullptr)
			continue;
		peekState()->input();
		peekState()->update(dt);
		this->m_Window.clear(sf::Color::Black);
		peekState()->draw(dt);
		this->m_Window.display();
	}
}

void Game::loadTextures()
{
	m_TextureManager.loadTexture("player", "graphics/shipThree.png");
	m_TextureManager.loadTexture("enemy", "graphics/shipThree.png");

	m_TextureManager.loadTexture("background", "graphics/background.png");
}

void Game::loadFonts()
{
	sf::Font font;
	font.loadFromFile("fonts/game_sans_serif_7.ttf");
	this->m_Fonts["main_font"] = font;
	return;
}

/* http://www.w3schools.com/colors/colors_picker.asp */
void Game::loadStyleSheets()
{
	this->m_StyleSheets["text"] = GUIStyle(&this->m_Fonts.at("main_font"), 1,
		sf::Color(0xc6, 0xc6, 0xc6), sf::Color(0x94, 0x94, 0x94), sf::Color(0x00, 0x00, 0x00),
		sf::Color(0x61, 0x61, 0x61), sf::Color(0x94, 0x94, 0x94), sf::Color(0x00, 0x00, 0x00));
	this->m_StyleSheets["hud"] = GUIStyle(&this->m_Fonts.at("main_font"), 0,
		sf::Color(102, 0, 102, 50), sf::Color(0, 0, 0, 0), sf::Color(204, 102, 0, 255),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0));
	this->m_StyleSheets["button"] = GUIStyle(&this->m_Fonts.at("main_font"), 3,
		sf::Color(0, 0, 255, 50), sf::Color(0, 102, 102, 25), sf::Color(128, 0, 0, 255),
		sf::Color(0, 102, 204, 40), sf::Color(0, 102, 102, 50), sf::Color(204, 51, 0, 255));
	this->m_StyleSheets["menu"] = GUIStyle(&this->m_Fonts.at("main_font"), 0,
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(102, 0, 204, 255),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(153, 0, 0, 255));

	return;
}

Game::Game()
{
	this->loadTextures();
	this->loadFonts();
	this->loadStyleSheets();

	this->m_Window.create(sf::VideoMode(1000, 800), "FarOut");
	this->m_Window.setFramerateLimit(60);

	this->m_Background.setTexture(this->m_TextureManager.getRef("background"));
}

Game::~Game()
{
	while (!this->m_States.empty())
		popState();
}