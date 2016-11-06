#include <iostream>
#include "screenMenu.hpp"

#include <SFML/Graphics.hpp>

using namespace sf;

screenMenu::screenMenu(void)
{
	alpha_max = 3 * 255;
	alpha_div = 3;
	playing = false;
}

int screenMenu::Run(RenderWindow &window)
{
	Event Event;
	bool Running = true;
	Texture textureBackground;
	Sprite spriteBackground;
	int alpha = 0;
	Font font;
	Text optionPlay;
	Text optionExit;
	Text optionContinue;
	int menu = 0;

	if (!textureBackground.loadFromFile("graphics/backgroundMenu.png"))
	{
		std::cerr << "Error loading graphics/backgroundMenu.png" << std::endl;
		return (-1);
	}
	spriteBackground.setTexture(textureBackground);
	if (!font.loadFromFile("fonts/Game Robot.ttf"))
	{
		std::cerr << "Error loading fonts/Game Robot.ttf" << std::endl;
		return (-1);
	}
	optionPlay.setFont(font);
	optionPlay.setCharacterSize(100);
	optionPlay.setString("Play");
	optionPlay.setPosition({ VideoMode::getDesktopMode().width / 2.2f, VideoMode::getDesktopMode().height / 3.0f });

	optionExit.setFont(font);
	optionExit.setCharacterSize(100);
	optionExit.setString("Exit");
	optionExit.setPosition({ VideoMode::getDesktopMode().width / 2.2f, VideoMode::getDesktopMode().height / 2.0f });

	optionContinue.setFont(font);
	optionContinue.setCharacterSize(100);
	optionContinue.setString("Continue");
	optionContinue.setPosition({ VideoMode::getDesktopMode().width / 2.2f, VideoMode::getDesktopMode().height / 3.0f });

	if (playing)
	{
		alpha = alpha_max;
	}

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
				case Keyboard::Up:
					menu = 0;
					break;
				case Keyboard::Down:
					menu = 1;
					break;
				case Keyboard::Return:
					if (menu == 0)
					{
						//Let's get play !
						playing = true;
						return (1);
					}
					else
					{
						//Let's get work...
						return (-1);
					}
					break;
				default:
					break;
				}
			}
		}
		//When getting at alpha_max, we stop modifying the sprite
		if (alpha<alpha_max)
		{
			alpha++;
		}
		spriteBackground.setColor(Color(255, 255, 255, alpha / alpha_div));
		if (menu == 0)
		{
			optionPlay.setFillColor(Color(255, 0, 0, 255));
			optionExit.setFillColor(Color(255, 255, 255, 255));
			optionContinue.setFillColor(Color(255, 0, 0, 255));
		}
		else
		{
			optionPlay.setFillColor(Color(255, 255, 255, 255));
			optionExit.setFillColor(Color(255, 0, 0, 255));
			optionContinue.setFillColor(Color(255, 255, 255, 255));
		}

		//Clearing screen
		window.clear();
		//Drawing
		window.draw(spriteBackground);
		if (alpha == alpha_max)
		{
			if (playing)
			{
				window.draw(optionContinue);
			}
			else
			{
				window.draw(optionPlay);
			}
			window.draw(optionExit);
		}
		window.display();
	}

	//Never reaching this point normally, but just in case, exit the application
	return (-1);
}