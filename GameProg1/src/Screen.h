#pragma once
#include <SFML/Graphics.hpp>

class Screen
{
public:
	virtual int Run(sf::RenderWindow &window) = 0;
};