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
	
	bgTitle = new Sprite("assets/bg_title.png");

	titleStage = new TitleStage(this);

	renderTexture = LoadRenderTexture(gameWidth, gameHeight);

	SetTargetFPS(fps);
}

void Game::cleanUp()
{
	bgTitle->unload();
	UnloadRenderTexture(renderTexture);
}

void Game::run()
{
	bool gameEnd = false;

	while(!gameEnd)
	{

		if(IsKeyDown(KEY_ESCAPE) || WindowShouldClose())
			gameEnd = true;

		BeginDrawing();
		BeginTextureMode(renderTexture);

		switch (state)
		{
		case 1:
			break;
		
		default:
			titleStage->run();
			break;
		}


		EndTextureMode();

		EndDrawing();
	}

	cleanUp();
	CloseWindow();
}