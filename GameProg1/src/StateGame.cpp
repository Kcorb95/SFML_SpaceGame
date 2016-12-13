#include <SFML/Graphics.hpp>

#include "State.h"
#include "StateGame.h"
#include "StateMenu.h"
#include <iostream>
#include <random>

void StateGame::draw(const float dt)
{
	this->m_Game->m_Window.clear(sf::Color::Black);

	this->m_Game->m_Window.setView(this->m_GUIView);
	this->m_Game->m_Window.draw(this->m_Game->m_Background);

	this->m_Game->m_Window.setView(this->m_GameView);

	this->m_Game->m_PlayerShip.draw(this->m_Game->m_Window, dt);
	this->m_Game->m_EnemyShip.draw(this->m_Game->m_Window, dt);

	this->m_Game->m_Window.setView(this->m_GUIView);
	for (auto gui : this->m_GUISystem)
		this->m_Game->m_Window.draw(gui.second);

	return;
}

void StateGame::update(const float dt)
{
	//update for the guisystem
	//update ammo etc
	this->m_Game->m_PlayerShip.update();
	this->m_Game->m_EnemyShip.update();

	if (m_ActionState == ActionState::ACTION)
	{
		enemyAction();
		m_ActionState = ActionState::IDLE;
	}
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
			this->m_GUISystem.at("itemMenu").highlight(this->m_GUISystem.at("itemMenu").getEntry(guiPos));
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
					this->m_GUISystem.at("itemMenu").show();
					this->m_GUISystem.at("backButton").show();
					this->m_GUISystem.at("actionMenu").hide();
				}
			}
			else
			{
				std::string msg = this->m_GUISystem.at("backButton").activate(guiPos);
				if (msg == "back")
				{
					this->m_GUISystem.at("attackMenu").hide();
					this->m_GUISystem.at("itemMenu").hide();
					this->m_GUISystem.at("backButton").hide();
					this->m_GUISystem.at("actionMenu").show();
				}
				else
				{
					std::string msg = this->m_GUISystem.at("attackMenu").activate(guiPos);
					if (msg.std::string::find("weapon") != std::string::npos && m_ActionState == ActionState::IDLE)
					{
						int selection = std::stoi(msg.std::string::substr(7, 1));
						if (this->m_Game->m_PlayerShip.getWeapon(selection).getCurrentAmmo() > 0)//Does the player have the ammo to do this?
						{
							this->m_Game->m_PlayerShip.getWeapon(selection).decreaseAmmo();//Decrease ammo and fire weapons
							int hitChance = random(100);
							if (hitChance < this->m_Game->m_PlayerShip.getWeapon(selection).getHitChance() + this->m_Game->m_PlayerShip.getEvasion())//Does it hit?
							{
								this->m_Game->m_PlayerShip.getWeapon(selection).playSound(this->m_Game->m_SoundManager);
								this->m_Game->m_EnemyShip.damage(this->m_Game->m_PlayerShip.getWeapon(selection));
								this->m_GUISystem.at("enemyHud").m_Entries.at(0).m_Text.setString("Armor: " + std::to_string(this->m_Game->m_EnemyShip.getCurrentArmor()));
								this->m_GUISystem.at("enemyHud").m_Entries.at(1).m_Text.setString("Structure: " + std::to_string(this->m_Game->m_EnemyShip.getCurrentStructure()));
							}
							else
							{
								srand(time(NULL));
								std::string r = std::to_string(rand() % (2 - 1) + 1);

								this->m_Game->m_SoundManager.getRef("miss" + r).play();
								std::cerr << "Player Miss!! || " << hitChance << std::endl;
							}
							this->m_GUISystem.at("attackMenu").m_Entries.at(selection).m_Text.setString(this->m_Game->m_PlayerShip.getWeapon(selection).getName() +
								" Ammo: " + std::to_string(this->m_Game->m_PlayerShip.getWeapon(selection).getCurrentAmmo()) + "/" + std::to_string(this->m_Game->m_PlayerShip.getWeapon(selection).getMaxAmmo()));
							//Update GUI for decreased ammo (maybe make gui update method)

							this->m_ActionState = ActionState::ACTION;

							this->m_GUISystem.at("attackMenu").hide();
							this->m_GUISystem.at("backButton").hide();
							this->m_GUISystem.at("actionMenu").show();
						}
					}
					else
					{
						std::string msg = this->m_GUISystem.at("itemMenu").activate(guiPos);
						if (msg.std::string::find("item") != std::string::npos && m_ActionState == ActionState::IDLE)
						{
							int selection = std::stoi(msg.std::string::substr(5, 1));
							this->m_Game->m_PlayerShip.useItem(this->m_Game->m_PlayerShip.getItem(selection));
							this->m_Game->m_SoundManager.getRef("itemUse").play();
							//Remove the used item from inventory (maybe have multi-use items)
							std::swap(m_Game->m_PlayerShip.m_Items.at(selection), m_Game->m_PlayerShip.m_Items.back());//swap used item with item at back of array
							m_Game->m_PlayerShip.m_Items.pop_back();//pop the last element off
							this->m_GUISystem.erase("itemMenu");//erase old itemMenu

							updateItems();//create new item menu
							//Update GUI for decreased ammo (maybe make gui update method)
						}

						this->m_ActionState = ActionState::ACTION;

						this->m_GUISystem.at("itemMenu").hide();
						this->m_GUISystem.at("backButton").hide();
						this->m_GUISystem.at("actionMenu").show();
					}
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

	/*
	************
	* Player HUD
	************
	*/
	this->m_GUISystem.emplace("playerHud", GUI(sf::Vector2f(210, 30), 2, false, this->m_Game->m_StyleSheets.at("hud"),
	{
		std::make_pair("Armor: " + std::to_string(this->m_Game->m_PlayerShip.getCurrentArmor()), "armor"),
		std::make_pair("Structure: " + std::to_string(this->m_Game->m_PlayerShip.getCurrentStructure()), "structure")
	}));

	/*
	***********
	* Enemy HUD
	***********
	*/
	this->m_GUISystem.emplace("enemyHud", GUI(sf::Vector2f(210, 30), 2, false, this->m_Game->m_StyleSheets.at("hud"),
	{
		std::make_pair("Armor: " + std::to_string(this->m_Game->m_EnemyShip.getCurrentArmor()), "armor"),
		std::make_pair("Structure: " + std::to_string(this->m_Game->m_EnemyShip.getCurrentStructure()), "structure")
	}));

	/*
	 *************
	 * Action Menu
	 *************
	 */
	this->m_GUISystem.emplace("actionMenu", GUI(sf::Vector2f(175, 40), 2, false, this->m_Game->m_StyleSheets.at("button"),
	{
		std::make_pair("Attack!", "attack"),
		std::make_pair("Use Item", "useItem")
	}));

	/*
	*************
	* Attack Menu
	*************
	*/
	//Create a vector of weapon pairs
	std::vector<std::pair<std::string, std::string>> weapons;
	//Populate the vector based on current weapons owned by player
	for (int i = 0; i < game->m_PlayerShip.m_Weapons.size(); i++)
	{
		weapons.push_back(
			std::make_pair(game->m_PlayerShip.getWeapon(i).getName() +
				" Ammo: " + std::to_string(game->m_PlayerShip.getWeapon(i).getCurrentAmmo()) + "/" + std::to_string(game->m_PlayerShip.getWeapon(i).getMaxAmmo()),
				"weapon_" + std::to_string(i)));
	}
	this->m_GUISystem.emplace("attackMenu", GUI(sf::Vector2f(500, 30), 2, false, this->m_Game->m_StyleSheets.at("button"), weapons));

	/*
	***********
	* Item Menu
	***********
	*/
	//Create a vector of item pairs
	//Populate vector
	for (int i = 0; i < game->m_PlayerShip.m_Items.size(); i++)
	{
		Item& item = game->m_PlayerShip.getItem(i);
		this->m_Game->m_PlayerShip.m_ItemPairs.push_back(
			std::make_pair(item.getName() +
				" | Strength: " + std::to_string(item.getStrength()) +
				" | Turns: " + std::to_string(item.getDuration()),
				"item_" + std::to_string(i)));
	}
	this->m_GUISystem.emplace("itemMenu", GUI(sf::Vector2f(550, 30), 2, false, this->m_Game->m_StyleSheets.at("button"), this->m_Game->m_PlayerShip.m_ItemPairs));

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
	this->m_GUISystem.at("playerHud").setOrigin(0, 0);
	this->m_GUISystem.at("playerHud").setPosition(15, 10);
	this->m_GUISystem.at("playerHud").show();
	//Draw Enemy HUD
	this->m_GUISystem.at("enemyHud").setOrigin(this->m_GUISystem.at("enemyHud").getSize().x, 0);
	this->m_GUISystem.at("enemyHud").setPosition(sf::Vector2f(this->m_Game->m_Window.getSize().x - 40, 10));
	this->m_GUISystem.at("enemyHud").show();

	//set origin of this menu to the center bottom of the GUI
	this->m_GUISystem.at("actionMenu").setOrigin(this->m_GUISystem.at("actionMenu").getSize().x * 0.5f, this->m_GUISystem.at("actionMenu").getSize().y);
	this->m_GUISystem.at("actionMenu").setPosition(sf::Vector2f(this->m_Game->m_Window.getSize().x * 0.5, this->m_Game->m_Window.getSize().y - 25));
	this->m_GUISystem.at("actionMenu").show();

	this->m_GUISystem.at("attackMenu").setOrigin(this->m_GUISystem.at("attackMenu").getSize().x * 0.5f, this->m_GUISystem.at("attackMenu").getSize().y);
	this->m_GUISystem.at("attackMenu").setPosition(sf::Vector2f(this->m_Game->m_Window.getSize().x * 0.5, this->m_Game->m_Window.getSize().y - 25));

	this->m_GUISystem.at("itemMenu").setOrigin(this->m_GUISystem.at("itemMenu").getSize().x * 0.5f, this->m_GUISystem.at("itemMenu").getSize().y);
	this->m_GUISystem.at("itemMenu").setPosition(sf::Vector2f(this->m_Game->m_Window.getSize().x * 0.5 - 50, this->m_Game->m_Window.getSize().y - 25));

	this->m_GUISystem.at("backButton").setOrigin(this->m_GUISystem.at("backButton").getSize().x * 0.5f, this->m_GUISystem.at("backButton").getSize().y);
	this->m_GUISystem.at("backButton").setPosition(sf::Vector2f(this->m_Game->m_Window.getSize().x * 0.5 + 400, this->m_Game->m_Window.getSize().y - 5));

	//Play m_GameMusic
	this->m_Game->m_MenuMusic.stop();
	this->m_Game->m_GameMusic.play();

}

void StateGame::enemyAction()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(0, std::nextafter(5, DBL_MAX));
	auto found = false;
	int weaponSelection;
	int hitChance;

	while (!found)
	{
		weaponSelection = random(this->m_Game->m_EnemyShip.m_Weapons.size());
		if (this->m_Game->m_EnemyShip.getWeapon(weaponSelection).getCurrentAmmo() > 0)//is there enough ammo to do this?
		{
			hitChance = random(100);
			if (hitChance < this->m_Game->m_EnemyShip.getWeapon(weaponSelection).getHitChance())//if odd
			{
				fireWeapon(weaponSelection);//hit
			}
			else
				std::cerr << "Enemy Miss!! || " << hitChance << std::endl;
			found = true;
		}
		else { std::cerr << "Not Enough Ammo" << std::endl; }
	}

	this->m_GUISystem.at("playerHud").m_Entries.at(0).m_Text.setString("Armor: " + std::to_string(this->m_Game->m_PlayerShip.getCurrentArmor()));
	this->m_GUISystem.at("playerHud").m_Entries.at(1).m_Text.setString("Structure: " + std::to_string(this->m_Game->m_PlayerShip.getCurrentStructure()));

	if (!this->m_Game->m_PlayerShip.isAlive)
	{
		std::cerr << "You Lose!!";
		this->m_Game->pushState(new StateMenu(this->m_Game));//Go to main menu
	}
}

void StateGame::fireWeapon(const int index)
{
	this->m_Game->m_PlayerShip.damage(this->m_Game->m_EnemyShip.getWeapon(index));//deal the damage to the player based on the randomly chosen enemy weapon
	this->m_Game->m_EnemyShip.getWeapon(index).decreaseAmmo();//decrease the ammo for the chosen weapon
	std::cerr << "Firing: " << this->m_Game->m_EnemyShip.getWeapon(index).getName()
		<< " Ammo: " << std::to_string(this->m_Game->m_EnemyShip.getWeapon(index).getCurrentAmmo()) << std::endl;
}

int StateGame::random(int range)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(0, std::nextafter(range, DBL_MAX));
	return (int)dist(mt);
}

void StateGame::updateItems()
{
	this->m_Game->m_PlayerShip.m_ItemPairs.clear();
	for (int i = 0; i < this->m_Game->m_PlayerShip.m_Items.size(); i++) {
		Item& item = this->m_Game->m_PlayerShip.getItem(i);
		this->m_Game->m_PlayerShip.m_ItemPairs.push_back(
			std::make_pair(item.getName() +
				" | Strength: " + std::to_string(item.getStrength()) +
				" | Turns: " + std::to_string(item.getDuration()),
				"item_" + std::to_string(i)));
	}
	this->m_GUISystem.emplace("itemMenu", GUI(sf::Vector2f(550, 30), 2, false, this->m_Game->m_StyleSheets.at("button"), this->m_Game->m_PlayerShip.m_ItemPairs));

	this->m_GUISystem.at("itemMenu").setOrigin(this->m_GUISystem.at("itemMenu").getSize().x * 0.5f, this->m_GUISystem.at("itemMenu").getSize().y);
	this->m_GUISystem.at("itemMenu").setPosition(sf::Vector2f(this->m_Game->m_Window.getSize().x * 0.5, this->m_Game->m_Window.getSize().y - 25));
}