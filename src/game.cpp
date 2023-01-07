#include "game.hpp"

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

	player = new Player();

	//load castle textures
	loadTextures(CASTLE_TEXTURE_COUNT, CASTLE_TEXTURE_PATH, CASTLE_FNAME_PREFIX);

	stageStart = LoadMusicStream("assets/stage_start.mp3");
	bgm1 = LoadMusicStream("assets/bgm1.mp3");

	titleStage = new TitleStage(this, gameWidth, gameHeight);
	levelOne = new GameStage(this, 272, GAME_HEIGHT, level1, "STAGE 1", bgm1, 128, 144);

	SetTargetFPS(fps);
}

void Game::cleanUp()
{
	player->unload();
	UnloadMusicStream(stageStart);
	UnloadMusicStream(bgm1);
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
			levelOne->run();
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

	//manual load
	textures["hud"] = LoadTexture("assets/hud.png");
}

void Game::unloadTextures()
{
	for (auto const& t : textures)
	{
		UnloadTexture(t.second);
	}
}