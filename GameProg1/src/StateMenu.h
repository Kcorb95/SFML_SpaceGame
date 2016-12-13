#pragma once

#include <SFML/Graphics.hpp>
#include <map>

#include "State.h"
#include "GUI.h"

class StateMenu : public State
{
private:
	sf::View m_View;

	std::map<std::string, GUI> m_GUISystem;

	void loadGame();

public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void input();

	StateMenu(Game* game);
};