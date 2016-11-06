#include <iostream>
#include "screenGame.hpp"
#include "player.h"
#include <SFML/Graphics.hpp>

using namespace sf;

screenGame::screenGame(void)
{
	
}

int screenGame::Run(RenderWindow &window)
{
	// Start with the GAME_OVER state
	State state = State::GAME_OVER;
	// Get the screen resolution and create an SFML window
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	Event Event;
	bool Running = true;
	Texture textureBackground;
	Sprite spriteBackground;
	Player player;
	IntRect space;
	//TODO Make work with texture handler
	if (!textureBackground.loadFromFile("graphics/backgroundLevelOne.png"))
	{
		std::cerr << "Error loading graphics/backgroundLevelOne.png" << std::endl;
		return (-1);
	}
	spriteBackground.setTexture(textureBackground);


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
				player.resetPlayerStats();
			}
		}//End Event polling

		if (state == State::PLAYING)
		{

		}//end controls handling

		if (state == State::PLAYING)
		{
			player.spawn(resolution);
		}//end start setup
		
		if (state == State::PLAYING)
		{

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
			//Drawing
			window.draw(spriteBackground);
			window.draw(player.getSprite());
		}

		window.display();
	}

	//Never reaching this point normally, but just in case, exit the application
	return -1;
}