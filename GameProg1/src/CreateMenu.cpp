//#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "FarOut.h"

int createMenu(State state)
{
	// Create a texture to hold a graphic on the GPU
	Texture textureBackground;
	Texture textureStart;
	Texture textureExit;

	// Load a graphic into the texture
	textureBackground.loadFromFile("graphics/menu.png");
	textureStart.loadFromFile("graphics/start.png");
	textureExit.loadFromFile("graphics/exit.png");

	// Create a sprite for the background, start and exit textures
	Sprite spriteBackground;
	Sprite spriteStart;
	Sprite spriteExit;


	// Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);
	spriteStart.setTexture(textureStart);
	spriteExit.setTexture(textureExit);


	// Set the spriteBackground to cover the screen
	spriteBackground.setPosition(0, 0);
	spriteStart.setPosition(0, 100);
	spriteExit.setPosition(0, 200);




	if (state == State::MENU)
	{

	}
	else if (state == State::PAUSED)
	{

	}
}