#pragma once

using namespace sf;

// The game will always be in one of these states
enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING, MENU };

int createBackground(VertexArray& rVA, IntRect arena);
