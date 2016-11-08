#include <iostream>
#include <SFML/Graphics.hpp>
#include "ScreenReference.h"

using namespace sf;

int main(int argc, char** argv)
{
	//Applications variables
	std::vector<Screen*> Screens;
	int screen = 0;

	// Get the screen resolution and create an SFML window
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y), "FarOut", Style::Fullscreen);

	//Screens preparations
	ScreenMenu sM;
	Screens.push_back(&sM);
	ScreenGame sG;
	Screens.push_back(&sG);

	//Main loop
	while (screen >= 0)
	{
		screen = Screens[screen]->Run(window);
	}

	return EXIT_SUCCESS;
}