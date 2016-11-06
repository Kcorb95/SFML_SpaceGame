#pragma once
#include "cScreen.hpp"
#include <SFML\Graphics.hpp>

using namespace sf;

// The game will always be in one of these states
enum class State { GAME_OVER, PLAYING };

class screenGame : public cScreen
{
private:

public:
	screenGame(void);
	virtual int Run(sf::RenderWindow &window);
};