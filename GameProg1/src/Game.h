#pragma once

#include <SFML/Graphics.hpp>
#include <stack>

#include "TextureManager.h"
#include "GUI.h"
#include "Ship.h"
#include "SoundManager.h"

class State;

class Game
{
private:
	void loadTextures();
	void loadSounds();
	void loadStyleSheets();
	void loadFonts();
	void loadShips();

public:
	std::stack<State*> m_States;

	sf::RenderWindow m_Window;
	TextureManager m_TextureManager;
	SoundManager m_SoundManager;
	sf::Sprite m_Background;

	Ship m_PlayerShip;
	Ship m_EnemyShip;

	sf::Music m_GameMusic;
	sf::Music m_MenuMusic;

	std::map<std::string, GUIStyle> m_StyleSheets;
	std::map<std::string, sf::Font> m_Fonts;

	void pushState(State* state);
	void popState();
	void changeState(State* state);
	State* peekState();

	void gameLoop();

	Game();
	~Game();
};