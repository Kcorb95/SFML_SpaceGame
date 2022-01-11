#include "Game.h"
#include "StateMenu.h"

int main()
{
	Game game;
	game.pushState(new StateMenu(&game));
	game.gameLoop();

	return 0;
}