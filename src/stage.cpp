#include "stage.hpp"

Stage::Stage(Game *gm, int width, int height)
{
	game = gm;
	state = 0;
	initialized = false;
	this->width = width;
	this->height = height;
	renderTexture = LoadRenderTexture(width, height);
};

void Stage::run()
{
	if (!initialized) {
		this->init();
		initialized = true;
	}
	this->draw();
	this->handleKeys();
}

void Stage::cleanUp()
{
	UnloadRenderTexture(renderTexture);
}


void TitleStage::init()
{
	bgTitle = new Sprite("assets/bg_title.png");
	ship = new Sprite("assets/ship_title.png");
	char1 = new Sprite("assets/char1_title.png");
	char2 = new Sprite("assets/char2_title.png");
	title = new Sprite("assets/text_title.png");
	enter = new Sprite("assets/press_enter_title.png");
	titleMusic = LoadMusicStream("assets/title.mp3");
	bomb = new Sprite("assets/bomb.png", 4);
	ship->x = (game->gameWidth / 2) - (ship->getTexture().width / 2);
	ship->y = -ship->getTexture().height;
	char1->x = 8;
	char1->y = -char1->getTexture().height;
	char2->x = game->gameWidth - (char2->getTexture().width + 35);
	char2->y = game->gameHeight;
	title->x = game->gameWidth;
	title->y = 5;
	bomb->x = ((game->gameWidth / 2) - (enter->getTexture().width / 2)) - 12;
	bomb->y = 150;
	enter->x = ((game->gameWidth / 2) - (enter->getTexture().width / 2)) + 12;
	enter->y = 150;
}

void TitleStage::handleKeys()
{
	if(IsKeyDown(KEY_ENTER))
	{
		StopMusicStream(titleMusic);
		game->state = 1;
		state = 0;
		initialized = false;
		this->cleanUp();
	}
}

void TitleStage::draw()
{
	BeginDrawing();
	BeginTextureMode(renderTexture);

	bgTitle->draw();
	ship->draw();
	char1->draw();
	char2->draw();
	title->draw();

	switch (state)
	{
	case 1:
		if (char1->y <= (game->gameHeight / 2) - (char1->getTexture().height / 2)) 
		{
			char1->y += 10;
		}
		if (char2->y >= 142)
		{
			char2->y -= 5;
		}
		else
		{
			state = 2;
		}
		break;

	case 2:
		if (title->x >= 5)
		{
			title->x -= 5;
		}
		else
		{
			PlayMusicStream(titleMusic);
			state = 3;
		}
		break;
	case 3:
		UpdateMusicStream(titleMusic);
		bomb->play();
		enter->draw();
		break;
	default:
		if (ship->y <= 20) 
		{
			ship->y += 1;
		}
		else
		{
			state = 1;
		}
		break;
	}

	EndTextureMode();
	ClearBackground(BLACK);

	Rectangle srcRect = (Rectangle){ 0.0, 0.0, static_cast<float>(game->gameWidth), static_cast<float>(-game->gameHeight) };
	Rectangle dstRect = (Rectangle) { static_cast<float>((game->screenWidth / 2.0) - ( (game->screenWidth * ((float)this->height / (float)this->width)) / 2.0)), 0.0, static_cast<float>(game->screenWidth * ((float)this->height / (float)this->width)), static_cast<float>(game->screenHeight) };
	DrawTexturePro(renderTexture.texture, srcRect , dstRect, (Vector2){ 0.0, 0.0 }, 0.0, WHITE);  
	EndDrawing();

}

void TitleStage::cleanUp()
{
	Stage::cleanUp();
	bgTitle->unload();
	ship->unload();
	char1->unload();
	char2->unload();
	title->unload();
	enter->unload();
	UnloadMusicStream(titleMusic);
}

GameStage::GameStage(Game *gm, int width, int height, vector<vector <string>> level, string title, Music bg, int px, int py) : Stage(gm, width, height)
{
	int currentX = 0;
	int currentY = 16;
	this->title = title;
	showCounter = 0;
	currentBg = bg;

	txtVec = MeasureTextEx(GetFontDefault(), this->title.c_str(), 40, 1.5);
	txtX = game->gameWidth;

	hud = new Sprite();
	hud->setTexture(game->textures["hud"]);

	for (auto& it1 : level)
	{
		currentX = 0;
		for(auto& it2 : it1)
		{
			Texture2D thisTexture = game->textures[it2];
			Sprite thisSprite(thisTexture.width / thisTexture.height);
			thisSprite.setTexture(thisTexture);
			thisSprite.x = currentX;
			thisSprite.y = currentY;
			tiles.push_back(thisSprite);
			currentX += 16;
		}

		currentY += 16;
	}
	game->player->x = px;
	game->player->y = py;
}

void GameStage::handleKeys()
{
	if (state == 2)
	{
		if (IsKeyDown(KEY_UP))
		{
			game->player->currentMovement = PLAYER_WALK_UP;
		}
		else if (IsKeyReleased(KEY_UP))
		{
			game->player->currentMovement = PLAYER_UP;
		}
		else if (IsKeyDown(KEY_DOWN))
		{
			game->player->currentMovement = PLAYER_WALK_DOWN;
		}
		else if (IsKeyReleased(KEY_DOWN))
		{
			game->player->currentMovement = PLAYER_DOWN;
		}
		else if (IsKeyDown(KEY_LEFT))
		{
			game->player->currentMovement = PLAYER_WALK_LEFT;
		}
		else if (IsKeyReleased(KEY_LEFT))
		{
			game->player->currentMovement = PLAYER_LEFT;
		}
		else if (IsKeyDown(KEY_RIGHT))
		{
			game->player->currentMovement = PLAYER_WALK_RIGHT;
		}
		else if (IsKeyReleased(KEY_RIGHT))
		{
			game->player->currentMovement = PLAYER_RIGHT;
		}

	}
}

void GameStage::draw()
{
	BeginDrawing();
	BeginTextureMode(renderTexture);
	ClearBackground(BLACK);
	switch (state)
	{
	case 1:
		UpdateMusicStream(game->stageStart);
		DrawTextEx(GetFontDefault(), title.c_str(), (Vector2){ (float)txtX, ((game->gameHeight / 2) - (txtVec.y / 2)) - 20 }, 40,1.5, GREEN);

		if (showCounter == 200) {
			if (txtX > -txtVec.x)
			{
				txtX -= 4;
			}
			else
			{
				StopMusicStream(game->stageStart);
				state = 2;
				PlayMusicStream(currentBg);
			} 
		}
		else
		{
			showCounter += 1;
		}

		break;
	case 2:
		UpdateMusicStream(currentBg);
		for (auto& it : tiles)
		{
			it.play();
		}

		hud->draw();
		game->player->play();

		break;
	
	default:
		UpdateMusicStream(game->stageStart);
		if (txtX > (game->gameWidth / 2) - (txtVec.x / 2))
		{
			txtX -= 4;
		} 
		else
		{
			state = 1;
		}

		DrawTextEx(GetFontDefault(), title.c_str(), (Vector2){ (float)txtX, ((game->gameHeight / 2) - (txtVec.y / 2)) - 20 }, 40,1.5, GREEN);
		break;

	}

	EndTextureMode();
	ClearBackground(BLACK);

	Rectangle srcRect = (Rectangle){ 0.0, 0.0, static_cast<float>(game->gameWidth), static_cast<float>(-game->gameHeight) };
	Rectangle dstRect = (Rectangle) { static_cast<float>((game->screenWidth / 2.0) - ( (game->screenWidth * ((float)this->height / (float)this->width)) / 2.0)), 0.0, static_cast<float>(game->screenWidth * ((float)this->height / (float)this->width)), static_cast<float>(game->screenHeight) };
	DrawTexturePro(renderTexture.texture, srcRect , dstRect, (Vector2){ 0.0, 0.0 }, 0.0, WHITE);  
	EndDrawing();
}

void GameStage::init()
{
	PlayMusicStream(game->stageStart);
}

void GameStage::cleanUp()
{

}