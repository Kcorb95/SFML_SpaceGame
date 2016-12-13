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
	m_TextureManager.loadTexture("player", "graphics/shipFourSheet.png");
	m_TextureManager.loadTexture("enemy", "graphics/shipFourSheet.png");

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

void Game::loadSounds()
{
	m_SoundManager.loadSound("railFire1", "sounds/railFire1.wav");
	m_SoundManager.loadSound("railFire2", "sounds/railFire2.wav");
	m_SoundManager.loadSound("railFire3", "sounds/railFire3.wav");
	m_SoundManager.loadSound("rockFire", "sounds/rockFire.wav");
	m_SoundManager.loadSound("miss1", "sounds/miss1.wav");
	m_SoundManager.loadSound("miss2", "sounds/miss2.wav");
	m_SoundManager.loadSound("itemUse", "sounds/itemUse.wav");

	this->m_GameMusic.openFromFile("sounds/gameMusic.wav");
	this->m_GameMusic.setLoop(true); 
	
	this->m_MenuMusic.openFromFile("sounds/menuMusic.ogg");
	this->m_MenuMusic.setLoop(true);
}

void Game::loadShips()//This will allow us to create all of the ships for the game and then draw them when needed
{
	/*Player Ship*/
	this->m_PlayerShip = Ship(100, 100, 10, //Structure/Armor/Evasion
	{ Weapon("Basic Railgun", "Kinetic", 6, 75, 75, 0, { "railFire1","railFire2","railFire3" }), Weapon("Basic Missile Launcher", "Ballistic", 15, 60, 15, 2, { "rockFire" }) }, //Weapons
	{ Item(ItemType::ArmorRepair, "Basic Armor Repair", 50, 1), Item(ItemType::EvasionBoost, "Small Thrust Booster", 10, 3) },//Items
		sf::Vector2f(150, 174), m_TextureManager.getRef("player"),//Dimensions and Texture
		{ Animation(0, 2, 0.3f), Animation(0, 2, 0.1f),Animation(0, 2, 0.3f) });//Animations

	this->m_PlayerShip.setPosition(sf::Vector2f(25, 400));//hard coded for now, possibly make resolution a variable

	/*Starter Enemy Ship*/
	this->m_EnemyShip = Ship(150, 150, 10, //Structure/Armor/Evasion
	{ Weapon("Medium Railgun", "Kinetic", 8, 70, 85, 0, {"railFire1","railFire2","railFire3"}), Weapon("Light Missile Launcher", "Ballistic", 10, 50, 5, 1, {"rockFire"}) }, //Weapons
	{ Item(ItemType::ArmorRepair, "Basic Armor Repair", 50, 1), Item(ItemType::EvasionBoost, "Small Thrust Booster", 10, 3) },//Items
		sf::Vector2f(150, 174), m_TextureManager.getRef("enemy"),//Dimensions and Texture
		{ Animation(0, 2, 0.3f), Animation(0, 2, 0.1f),Animation(0, 2, 0.3f) });//Animations
	this->m_EnemyShip.setRotation(180);
	this->m_EnemyShip.setPosition(sf::Vector2f(975, 400));
}

Game::Game()
{
	this->loadTextures();
	this->loadSounds();
	this->loadFonts();
	this->loadStyleSheets();
	this->loadShips();

	this->m_Window.create(sf::VideoMode(1000, 800), "FarOut");
	this->m_Window.setFramerateLimit(60);

	this->m_Background.setTexture(this->m_TextureManager.getRef("background"));
}

Game::~Game()
{
	while (!this->m_States.empty())
		popState();
}