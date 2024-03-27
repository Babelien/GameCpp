#include <iostream>
#include "game.h"

int main(int argc, char* argv[])
{
	Game game;

	const char* gameTitle = "Ushinokoku";

	if (game.initialize(gameTitle))
	{
		game.runLoop();
	}

	game.shutdown();

	return 0;
}