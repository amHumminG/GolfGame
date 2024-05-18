#include "Game.h"
#include "Wind.h"
#include <iostream>

int main()
{
	Game* game = new Game({1000, 0, 1000}, {0, 0, 0}, 1.0f, 65, 0.1f);

	game->Run();
	while (game->RepeatPlay())
	{
		// Play until exit
	}

	delete game;

	return 0;
}