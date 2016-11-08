#pragma once
#include "Screen.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

// The game will always be in one of these states
enum class State { GAME_OVER, PLAYING };

class ScreenGame : public Screen
{
public:
	// Get the screen resolution and create an SFML window
	Vector2f resolution;
	virtual int Run(sf::RenderWindow &window);
};