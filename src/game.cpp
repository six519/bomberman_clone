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

	//load castle textures
	loadTextures(CASTLE_TEXTURE_COUNT, CASTLE_TEXTURE_PATH, CASTLE_FNAME_PREFIX);

	titleStage = new TitleStage(this, gameWidth, gameHeight);

	SetTargetFPS(fps);
}

void Game::cleanUp()
{
	titleStage->cleanUp();
	unloadTextures();
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

void Game::loadTextures(int count, string path, string prefix)
{
	int n = 1;

	while(n < (count + 1))
	{
		textures[prefix + to_string(n)] = LoadTexture(("assets/" + path + prefix + to_string(n) + ".png").c_str());
		n++;
	}
}

void Game::unloadTextures()
{
	for (auto const& t : textures)
	{
		UnloadTexture(t.second);
	}
}