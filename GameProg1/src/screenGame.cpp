#include <iostream>
#include <sstream>
#include <fstream>
#include "ScreenGame.h"
#include "Player.h"
#include "Enemy.h"
#include "Action.h"
#include <SFML/Graphics.hpp>

using namespace sf;

int ScreenGame::Run(RenderWindow &window)
{
	// Start with the GAME_OVER state
	State state = State::GAME_OVER;
	// Get the screen resolution and create an SFML window
	Event Event;
	bool Running = true;
	Texture textureBackground;
	Sprite spriteBackground;
	Player Player;
	Enemy enemy;
	//TODO Make work with texture handler
	if (!textureBackground.loadFromFile("graphics/backgroundLevelOne.png"))
	{
		std::cerr << "Error loading graphics/backgroundLevelOne.png" << std::endl;
		return (-1);
	}
	spriteBackground.setTexture(textureBackground);

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	View viewMain(FloatRect(0, 0, resolution.x, resolution.y));

	/* --debug to show HUD bounds
	RectangleShape actionRect;
	actionRect.setSize(Vector2f(resolution.x/1.8, resolution.y/4));
	actionRect.setOrigin(Vector2f((resolution.x / 1.8) / 2, resolution.y / 4));
	actionRect.setPosition(Vector2f(resolution.x/2,resolution.y));
	actionRect.setFillColor(Color::Green);
	*/
	//Load font
	Font font;
	if (!font.loadFromFile("fonts/Gang Wolfik Craze.otf"))
	{
		std::cerr << "Error loading fonts/Gang Wolfik Craze.otf" << std::endl;
		return (-1);
	}

	//Player Armor
	Text textPlayerArmor;
	textPlayerArmor.setFont(font);
	textPlayerArmor.setCharacterSize(40);
	textPlayerArmor.setFillColor(Color::White);
	textPlayerArmor.setPosition(resolution.x / 40, resolution.y / 60);

	//Player Health
	Text textPlayerHealth;
	textPlayerHealth.setFont(font);
	textPlayerHealth.setCharacterSize(40);
	textPlayerHealth.setFillColor(Color::White);
	textPlayerHealth.setPosition(resolution.x / 40, resolution.y / 20);

	//Enemy Armor
	Text textEnemyArmor;
	textEnemyArmor.setFont(font);
	textEnemyArmor.setCharacterSize(40);
	textEnemyArmor.setFillColor(Color::White);
	textEnemyArmor.setPosition(resolution.x/1.2, resolution.y / 60);

	//Enemy Health
	Text textEnemyHealth;
	textEnemyHealth.setFont(font);
	textEnemyHealth.setCharacterSize(40);
	textEnemyHealth.setFillColor(Color::White);
	textEnemyHealth.setPosition(resolution.x/1.2, resolution.y / 20);
	
	Action action(Player);

	while (Running)
	{
		//Verifying events
		while (window.pollEvent(Event))
		{
			// Window closed
			if (Event.type == Event::Closed)
			{
				return (-1);
			}
			//Key pressed
			if (Event.type == Event::KeyPressed)
			{
				switch (Event.key.code)
				{
				case Keyboard::Escape:
					return (0);
					break;
				default:
					break;
				}
			}
			// Start a new game while in GAME_OVER state
			if (state == State::GAME_OVER)
			{
				state = State::PLAYING;
				//round info

				// Reset the player's stats
				Player.resetPlayerStats();
			}
		}//End Event polling

		//Handle controls while playing
		if (state == State::PLAYING)
		{

		}//end controls handling

		if (state == State::PLAYING)
		{
			Player.spawn();
			enemy.spawn(0);//spawn small enemy
		}//end start setup
		
		/*
		****************
		UPDATE THE FRAME
		****************
		*/
		if (state == State::PLAYING)
		{
			std::stringstream ssPlayerArmor;
			std::stringstream ssPlayerHealth;

			std::stringstream ssEnemyArmor;
			std::stringstream ssEnemyHealth;

			ssPlayerArmor << "Armor: " << Player.getArmor();
			ssPlayerHealth << "Health: " << Player.getHealth();
			ssEnemyArmor << "Armor: " << enemy.getArmor();
			ssEnemyHealth << "Health: " << enemy.getHealth();

			textPlayerArmor.setString(ssPlayerArmor.str());
			textPlayerHealth.setString(ssPlayerHealth.str());
			textEnemyArmor.setString(ssEnemyArmor.str());
			textEnemyHealth.setString(ssEnemyHealth.str());

			Player.update();
			enemy.update();
		}//end update scene

		 /*
		 **************
		 Draw the scene
		 **************
		 */

		if (state == State::PLAYING)
		{
			//Clearing screen
			window.clear();
			window.setView(viewMain);
			//Drawing main View
			window.draw(spriteBackground);
			window.draw(Player.getSprite());
			window.draw(enemy.getSprite());
			window.draw(textPlayerArmor);
			window.draw(textPlayerHealth);
			window.draw(textEnemyArmor);
			window.draw(textEnemyHealth);

			window.draw(action.m_Action);
			window.draw(action.m_Attack);
			//window.draw(actionRect); DEBUG FOR SHOWING HUDVIEW

			for (auto& text : action.m_TextWeapons)
			{
				window.draw(text);
			}
		}
		window.display();
	}
	//Never reaching this point normally, but just in case, exit the application
	return -1;
}