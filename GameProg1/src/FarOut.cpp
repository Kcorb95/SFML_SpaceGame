//#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "FarOut.h"

using namespace sf;

int main()
{
	// Start with the MENU state
	State state = State::MENU;


	// Get the screen resolution and create an SFML window
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y), "FarOut", Style::Fullscreen);

	// Create a an SFML View for the main action
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

	// Where is the mouse in relation to world coordinates
	Vector2f mouseWorldPosition;
	// Where is the mouse in relation to screen coordinates
	Vector2i mouseScreenPosition;

	// The main game loop
	while (window.isOpen())
	{
		/*
		************
		Handle input
		************
		*/

		// Handle events
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				// Pause a game while playing
				if (event.key.code == Keyboard::Escape && state == State::PLAYING)
				{
					state = State::PAUSED;
					//make menu
				}

				// Restart while paused
				else if (event.key.code == Keyboard::Escape &&
					state == State::PAUSED)
				{
					state = State::PLAYING;
				}
			}
		}//end event polling
	}
}