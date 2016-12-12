#pragma once

#include <SFML/Graphics.hpp>

#include "State.h"
#include "GUI.h"

enum class ActionState { IDLE, ACTION };

class StateGame : public State
{
private:
	std::map<std::string, GUI> m_GUISystem;

	ActionState m_ActionState;

	sf::View m_GameView;
	sf::View m_GUIView;

public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void input();

	StateGame(Game* game);

	void enemyAction();

	void fireWeapon(const int index);

	int random(int range);

	void updateItems();
};