#include <iostream>
#include "settings.hpp"
#include "game.hpp"

int main()
{
    Game game(TITLE, SCREEN_WIDTH, SCREEN_HEIGHT, GAME_WIDTH, GAME_HEIGHT, TARGET_FPS);
	game.run();

	return EXIT_SUCCESS;
}