#include <iostream>
#include "screenGame.hpp"

#include <SFML/Graphics.hpp>

using namespace sf;

screenGame::screenGame(void)
{

}

int screenGame::Run(RenderWindow &window)
{
	Event Event;
	bool Running = true;
	Texture textureBackground;
	Sprite spriteBackground;

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
		}

		//Clearing screen
		window.clear();
		//Drawing
		window.draw(spriteBackground);
		window.display();
	}

	//Never reaching this point normally, but just in case, exit the application
	return -1;
}