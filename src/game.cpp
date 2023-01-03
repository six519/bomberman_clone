#include "game.hpp"
#include <raylib.h>

Game::Game(string t, int sw, int sh, int gw, int gh, int fps)
{
	title = t;
	screenWidth = sw;
	screenHeight = sh;
	gameWidth = gw;
	gameHeight = gh;
	state = 0;

	InitWindow(screenWidth, screenHeight, title.c_str());
	InitAudioDevice();

	titleStage = new TitleStage(this, gameWidth, gameHeight);

	SetTargetFPS(fps);
}

void Game::cleanUp()
{
	titleStage->cleanUp();
	CloseAudioDevice();
}

void Game::run()
{
	bool gameEnd = false;

	while(!gameEnd)
	{

		if(IsKeyDown(KEY_ESCAPE) || WindowShouldClose())
			gameEnd = true;

		switch (state)
		{
		case 1:
			break;
		
		default:
			titleStage->run();
			break;
		}
	}

	cleanUp();
	CloseWindow();
}