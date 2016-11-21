#include <SFML/Graphics.hpp>

#include "State.h"
#include "StateGame.h"
#include "FarOut.h"
#include "StateMenu.h"

void StateGame::draw(const float dt)
{
	this->m_Game->m_Window.clear(sf::Color::Black);

	this->m_Game->m_Window.setView(this->m_GUIView);
	this->m_Game->m_Window.draw(this->m_Game->m_Background);

	this->m_Game->m_Window.setView(this->m_GameView);

	this->m_Game->m_Window.draw(this->m_Game->m_Player.getSprite());
	this->m_Game->m_Window.draw(this->m_Game->m_Enemy.getSprite());

	this->m_Game->m_Window.setView(this->m_GUIView);
	for (auto gui : this->m_GUISystem)
		this->m_Game->m_Window.draw(gui.second);

	return;
}

void StateGame::update(const float dt)
{
	//update for the guisystem
	//update ammo etc
	this->m_Game->m_Player.update();
	this->m_Game->m_Enemy.update();
	return;
}

void StateGame::input()
{
	sf::Event event;

	sf::Vector2f guiPos = this->m_Game->m_Window.mapPixelToCoords(sf::Mouse::getPosition(this->m_Game->m_Window), this->m_GUIView);
	sf::Vector2f gamePos = this->m_Game->m_Window.mapPixelToCoords(sf::Mouse::getPosition(this->m_Game->m_Window), this->m_GameView);

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
			this->m_GameView.setSize(event.size.width, event.size.height);
			this->m_GUIView.setSize(event.size.width, event.size.height);
			this->m_Game->m_Background.setPosition(this->m_Game->m_Window.mapPixelToCoords(sf::Vector2i(0, 0), this->m_GUIView));
			this->m_Game->m_Background.setScale(
				float(event.size.width) / float(this->m_Game->m_Background.getTexture()->getSize().x),
				float(event.size.height) / float(this->m_Game->m_Background.getTexture()->getSize().y));
			break;
		}
		case sf::Event::MouseMoved:
		{
			//do an action state thing here eventually so that only when attack state etc
			this->m_GUISystem.at("actionMenu").highlight(this->m_GUISystem.at("actionMenu").getEntry(guiPos));
			this->m_GUISystem.at("attackMenu").highlight(this->m_GUISystem.at("attackMenu").getEntry(guiPos));
			this->m_GUISystem.at("backButton").highlight(this->m_GUISystem.at("backButton").getEntry(guiPos));
			break;
		}
		case sf::Event::MouseButtonPressed:
		{
			//same as above
			if (this->m_GUISystem.at("actionMenu").m_Visible)
			{
				std::string msg = this->m_GUISystem.at("actionMenu").activate(guiPos);
				if (msg == "attack")
				{
					this->m_GUISystem.at("attackMenu").show();
					this->m_GUISystem.at("backButton").show();
					this->m_GUISystem.at("actionMenu").hide();
				}
				else if (msg == "useItem")
				{
				}
			}
			else if (this->m_GUISystem.at("backButton").m_Visible)
			{
				std::string msg = this->m_GUISystem.at("backButton").activate(guiPos);
				if (msg == "back")
				{
					this->m_GUISystem.at("attackMenu").hide();
					this->m_GUISystem.at("backButton").hide();
					this->m_GUISystem.at("actionMenu").show();
				}
			}
		}
		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::Escape)
				this->m_Game->pushState(new StateMenu(this->m_Game));
			break;
		}
		default:
			break;
		}
	}
	return;
}

//Main Constructor
StateGame::StateGame(Game* game)
{
	this->m_Game = game;
	sf::Vector2f pos = sf::Vector2f(this->m_Game->m_Window.getSize());
	this->m_GUIView.setSize(pos);
	this->m_GameView.setSize(pos);
	pos *= 0.5f;
	this->m_GUIView.setCenter(pos);
	this->m_GameView.setCenter(pos);

	//Spawn Ship and position sprite in middle left/right of screen
	this->m_Game->m_Player.spawn(Vector2f(25, this->m_Game->m_Window.getSize().y * 0.5f));
	this->m_Game->m_Enemy.spawn(1, Vector2f(this->m_Game->m_Window.getSize().x - 25, this->m_Game->m_Window.getSize().y * 0.5f));

	/*
	************
	* Player HUD
	************
	*/
	this->m_GUISystem.emplace("playerHud", GUI(sf::Vector2f(175, 30), 2, false, this->m_Game->m_StyleSheets.at("hud"),
	{
		std::make_pair("Armor: " + std::to_string(this->m_Game->m_Player.getArmor()), "armor"),
		std::make_pair("Health: " + std::to_string(this->m_Game->m_Player.getHealth()), "health")
	}));

	/*
	***********
	* Enemy HUD
	***********
	*/
	this->m_GUISystem.emplace("enemyHud", GUI(sf::Vector2f(175, 30), 2, false, this->m_Game->m_StyleSheets.at("hud"),
	{
		std::make_pair("Armor: " + std::to_string(this->m_Game->m_Enemy.getArmor()), "armor"),
		std::make_pair("Health: " + std::to_string(this->m_Game->m_Enemy.getHealth()), "health")
	}));

	/*
	 *************
	 * Action Menu
	 *************
	 */
	this->m_GUISystem.emplace("actionMenu", GUI(sf::Vector2f(175, 40), 2, false, this->m_Game->m_StyleSheets.at("button"),
	{
		std::make_pair("Attack!", "attack"),
		std::make_pair("Use Item", "use_item")
	}));

	/*
	*************
	* Attack Menu
	*************
	*/
	//Create a vector of weapon pairs
	std::vector<std::pair<std::string, std::string>> weapons;
	//Populate the vector based on current weapons owned by player
	for (int i = 0; i < game->m_Player.getCurrentWeapons(); i++)
	{
		weapons.push_back(
			std::make_pair(game->m_Player.getWeapon(i).getName() +
				" Ammo: " + std::to_string(game->m_Player.getWeapon(i).getCurrentAmmo()) + "/" + std::to_string(game->m_Player.getWeapon(i).getStartingAmmo()),
				"weapon_" + i));
	}
	this->m_GUISystem.emplace("attackMenu", GUI(sf::Vector2f(500, 30), 2, false, this->m_Game->m_StyleSheets.at("button"), weapons));

	/*
	*************
	* BackButton
	*************
	*/
	this->m_GUISystem.emplace("backButton", GUI(sf::Vector2f(175, 40), 2, false, this->m_Game->m_StyleSheets.at("button"),
	{
		std::make_pair("Back", "back")
	}));

	//Draw Player HUD
	this->m_GUISystem.at("playerHud").setOrigin(0,0);
	this->m_GUISystem.at("playerHud").setPosition(15, 10);
	this->m_GUISystem.at("playerHud").show();
	//Draw Enemy HUD
	this->m_GUISystem.at("enemyHud").setOrigin(this->m_GUISystem.at("enemyHud").getSize().x, 0);
	this->m_GUISystem.at("enemyHud").setPosition(sf::Vector2f(this->m_Game->m_Window.getSize().x - 15,10));
	this->m_GUISystem.at("enemyHud").show();

	//set origin of this menu to the center bottom of the GUI
	this->m_GUISystem.at("actionMenu").setOrigin(this->m_GUISystem.at("actionMenu").getSize().x * 0.5f, this->m_GUISystem.at("actionMenu").getSize().y);
	this->m_GUISystem.at("actionMenu").setPosition(sf::Vector2f(this->m_Game->m_Window.getSize().x * 0.5, this->m_Game->m_Window.getSize().y - 25));
	this->m_GUISystem.at("actionMenu").show();

	this->m_GUISystem.at("attackMenu").setOrigin(this->m_GUISystem.at("attackMenu").getSize().x * 0.5f, this->m_GUISystem.at("attackMenu").getSize().y);
	this->m_GUISystem.at("attackMenu").setPosition(sf::Vector2f(this->m_Game->m_Window.getSize().x * 0.5, this->m_Game->m_Window.getSize().y - 25));

	this->m_GUISystem.at("backButton").setOrigin(this->m_GUISystem.at("backButton").getSize().x * 0.5f, this->m_GUISystem.at("backButton").getSize().y);
	this->m_GUISystem.at("backButton").setPosition(sf::Vector2f(this->m_Game->m_Window.getSize().x * 0.5 + 400, this->m_Game->m_Window.getSize().y - 5));
}