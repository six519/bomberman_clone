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

	titleStage = new TitleStage(this);

	renderTexture = LoadRenderTexture(gameWidth, gameHeight);

	SetTargetFPS(fps);
}

void Game::cleanUp()
{
	titleStage->cleanUp();
	UnloadRenderTexture(renderTexture);
	CloseAudioDevice();
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
		ClearBackground(BLACK);

		Rectangle srcRect = (Rectangle){ 0.0, 0.0, static_cast<float>(renderTexture.texture.width), static_cast<float>(-renderTexture.texture.height) };
		Rectangle dstRect = (Rectangle) { static_cast<float>((screenWidth / 2.0) - ( (screenWidth * ((float)gameHeight / (float)gameWidth)) / 2.0)), 0.0, static_cast<float>(screenWidth * ((float)gameHeight / (float)gameWidth)), static_cast<float>(screenHeight) };
		DrawTexturePro(renderTexture.texture, srcRect , dstRect, (Vector2){ 0.0, 0.0 }, 0.0, WHITE);  
		EndDrawing();
	}

	cleanUp();
	CloseWindow();
}