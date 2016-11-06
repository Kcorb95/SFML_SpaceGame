#pragma once
#include "cScreen.hpp"
#include <SFML\Graphics.hpp>

using namespace sf;

// The game will always be in one of these states
enum class State { GAME_OVER, PLAYING };
// Start with the GAME_OVER state
State state = State::GAME_OVER;

class screenGame : public cScreen
{
private:
	float movement_step;
	float posx;
	float posy;
	sf::RectangleShape Rectangle;
public:
	screenGame(void);
	virtual int Run(sf::RenderWindow &window);
};