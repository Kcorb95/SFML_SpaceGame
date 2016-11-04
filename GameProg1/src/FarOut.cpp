// Include important C++ libraries here
#ifdef _MSC_VER
#include "stdafx.h"
#endif
#include <iostream>
#include <SFML/Graphics.hpp>
#include "screens.hpp"

using namespace sf;

int main(int argc, char** argv)
{
	//Applications variables
	std::vector<cScreen*> Screens;
	int screen = 0;

	// Get the screen resolution and create an SFML window
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y), "FarOut", Style::Fullscreen);

	//Screens preparations
	screenMenu sM;
	Screens.push_back(&sM);

	//Main loop
	while (screen >= 0)
	{
		screen = Screens[screen]->Run(window);
	}

	return EXIT_SUCCESS;
}