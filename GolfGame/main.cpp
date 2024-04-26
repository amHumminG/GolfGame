#include "Game.h"

int main()
{
	Game* game = new Game({1000, 0, 1000}, {0, 0, 0}, 1.0f, 50, 0.1f);

	game->Run();
	game->RepeatPlay();

	delete game;

	return 0;
}