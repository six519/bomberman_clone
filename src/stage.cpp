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
	ship->setMoveSpeed(SHIP_SPEED);
	char1 = new Sprite("assets/char1_title.png");
	char1->setMoveSpeed(CHAR_SPEED);
	char1->setMoveAmount(6);
	char2 = new Sprite("assets/char2_title.png");
	char2->setMoveAmount(3);
	char2->setMoveSpeed(CHAR_SPEED);
	title = new Sprite("assets/text_title.png");
	title->setMoveSpeed(CHAR_SPEED);
	title->setMoveAmount(8);
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
	char2->draw();
	title->draw();
	char1->draw();

	switch (state)
	{
	case 1:
		if (char2->y >= 142)
		{
			char2->moveUp();
		}

		if (char1->y <= 90) 
		{
			char1->moveDown();
		}
		else
		{
			state = 2;
		}
		break;


	case 2:
		if (title->x >= 5)
		{
			title->moveLeft();
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
			ship->moveDown();
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

GameStage::GameStage(Game *gm, int width, int height, vector<vector <string>> level, map<string,string> breakable, string title, Music bg, int px, int py) : Stage(gm, width, height)
{
	int currentX = 0;
	int currentY = 16;
	this->title = title;
	showCounter = 0;
	currentBg = bg;
	timeSeconds = 0;
	timeMinutes = 4;
	framesCounter = 0;

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

			if (find(notSolidList.begin(), notSolidList.end(), it2) != notSolidList.end())
			{
				thisSprite.solid = false;
			}

			if (find(floorList.begin(), floorList.end(), it2) != floorList.end())
			{
				thisSprite.is_floor = true;
			}

			tiles.push_back(thisSprite);

			if (breakable.count(to_string(currentX) + "," + to_string(currentY)) > 0)
			{
				Texture2D frontTexture = game->textures[breakable[to_string(currentX) + "," + to_string(currentY)]];
				Sprite frontSprite(frontTexture.width / frontTexture.height);
				frontSprite.setTexture(frontTexture);
				frontSprite.x = currentX;
				frontSprite.y = currentY;
				//frontSprite.backSprite = &thisSprite;
				//thisSprite = frontSprite;
				tiles.push_back(frontSprite);
			}

			currentX += 16;
		}

		currentY += 16;
	}
	game->player->x = px;
	game->player->y = py;
}

void GameStage::playerMove(int move)
{
	game->player->framesCounter++;

	if (game->player->framesCounter >= (TARGET_FPS / PLAYER_FRAME_SPEED))
	{
		game->player->framesCounter = 0;

		if (move == PLAYER_WALK_UP)
		{
			game->player->y -= PLAYER_SPEED;
		}
		else if (move == PLAYER_WALK_DOWN)
		{
			game->player->y += PLAYER_SPEED;
		}
		else if (move == PLAYER_WALK_LEFT)
		{
			game->player->x -= PLAYER_SPEED;
		}
		else if (move == PLAYER_WALK_RIGHT)
		{
			game->player->x += PLAYER_SPEED;
		}

	}
}

void GameStage::slideUporDown()
{
	if(game->player->collidedCount == 1)
	{
		if (game->player->x > game->player->lastCollidedX && ((game->player->lastCollidedX + 16) - game->player->x) <= 10)
		{
			game->player->x += PLAYER_SPEED;
		}
		else if (game->player->x < game->player->lastCollidedX && ((game->player->x + 16) - game->player->lastCollidedX) <= 10)
		{
			game->player->x -= PLAYER_SPEED;
		}
	}
}

void GameStage::slideLeftorRight()
{
	if(game->player->collidedCount == 1)
	{
		if ((game->player->y + 16) > game->player->lastCollidedY && ((game->player->lastCollidedY + 16) - (game->player->y + 16)) <= 10)
		{
			game->player->y += PLAYER_SPEED;
		}
		else if ((game->player->y + 16) < game->player->lastCollidedY && (((game->player->y + 16) + 16) - game->player->lastCollidedY) <= 10)
		{
			game->player->y -= PLAYER_SPEED;
		}
	}
}

void GameStage::handleKeys()
{
	if (state == 2)
	{
		// for movement
		if (IsKeyDown(KEY_UP))
		{
			game->player->currentMovement = PLAYER_WALK_UP;

			if (!(game->player->collided && (game->player->lastMovement == PLAYER_WALK_UP || game->player->lastMovement == PLAYER_UP)))
			{
				playerMove(PLAYER_WALK_UP);
			}
			else
			{
				slideUporDown();
			}

			if (game->player->collided)
			{
				if (game->player->lastMovement == PLAYER_WALK_LEFT)
				{
					game->player->x += PLAYER_SPEED;	
				}

				if (game->player->lastMovement == PLAYER_WALK_RIGHT)
				{
					game->player->x -= PLAYER_SPEED;	
				}

				if (game->player->lastMovement == PLAYER_WALK_DOWN)
				{
					game->player->y -= PLAYER_SPEED;	
				}

			}

		}
		else if (IsKeyReleased(KEY_UP))
		{
			game->player->currentMovement = PLAYER_UP;

			if (game->player->collided)
			{
				game->player->y += PLAYER_SPEED;
			}

		}
		else if (IsKeyDown(KEY_DOWN))
		{
			game->player->currentMovement = PLAYER_WALK_DOWN;

			if (!(game->player->collided && (game->player->lastMovement == PLAYER_WALK_DOWN || game->player->lastMovement == PLAYER_DOWN)))
			{
				playerMove(PLAYER_WALK_DOWN);
			}
			else
			{
				slideUporDown();
			}

			if (game->player->collided)
			{
				if (game->player->lastMovement == PLAYER_WALK_LEFT)
				{
					game->player->x += PLAYER_SPEED;	
				}

				if (game->player->lastMovement == PLAYER_WALK_RIGHT)
				{
					game->player->x -= PLAYER_SPEED;	
				}

				if (game->player->lastMovement == PLAYER_WALK_UP)
				{
					game->player->y += PLAYER_SPEED;	
				}

			}

		}
		else if (IsKeyReleased(KEY_DOWN))
		{
			game->player->currentMovement = PLAYER_DOWN;

			if (game->player->collided)
			{
				game->player->y -= PLAYER_SPEED;
			}

		}
		else if (IsKeyDown(KEY_LEFT))
		{
			game->player->currentMovement = PLAYER_WALK_LEFT;

			if (!(game->player->collided && (game->player->lastMovement == PLAYER_WALK_LEFT || game->player->lastMovement == PLAYER_LEFT)))
			{
				playerMove(PLAYER_WALK_LEFT);
			}
			else
			{
				slideLeftorRight();
			}

			if (game->player->collided)
			{
				if (game->player->lastMovement == PLAYER_WALK_RIGHT)
				{
					game->player->x -= PLAYER_SPEED;	
				}

				if (game->player->lastMovement == PLAYER_WALK_UP)
				{
					game->player->y += PLAYER_SPEED;	
				}

				if (game->player->lastMovement == PLAYER_WALK_DOWN)
				{
					game->player->y -= PLAYER_SPEED;	
				}
			}

		}
		else if (IsKeyReleased(KEY_LEFT))
		{
			game->player->currentMovement = PLAYER_LEFT;

			if (game->player->collided)
			{
				game->player->x += PLAYER_SPEED;
			}

		}
		else if (IsKeyDown(KEY_RIGHT))
		{
			game->player->currentMovement = PLAYER_WALK_RIGHT;

			if (!(game->player->collided && (game->player->lastMovement == PLAYER_WALK_RIGHT || game->player->lastMovement == PLAYER_RIGHT)))
			{
				playerMove(PLAYER_WALK_RIGHT);
			}
			else
			{
				slideLeftorRight();
			}

			if (game->player->collided)
			{
				if (game->player->lastMovement == PLAYER_WALK_LEFT)
				{
					game->player->x += PLAYER_SPEED;	
				}

				if (game->player->lastMovement == PLAYER_WALK_UP)
				{
					game->player->y += PLAYER_SPEED;	
				}

				if (game->player->lastMovement == PLAYER_WALK_DOWN)
				{
					game->player->y -= PLAYER_SPEED;	
				}

			}

		}
		else if (IsKeyReleased(KEY_RIGHT))
		{
			game->player->currentMovement = PLAYER_RIGHT;

			if (game->player->collided)
			{
				game->player->x -= PLAYER_SPEED;
			}

		}
		
		// for bomb
		if (IsKeyDown(KEY_SPACE))
		{
			if (game->player->canSpawnBomb)
			{
				game->player->canSpawnBomb = false;
				if (bombs.size() < game->player->bombCount && !game->player->isCollidedWithNotSolidBombs(bombs))
				{
					//spawn bomb
					Texture2D thisTexture = game->textures["bomb"];
					BombSprite thisSprite(thisTexture.width / thisTexture.height);
					thisSprite.setTexture(thisTexture);
					thisSprite.x = game->player->bombSnapX;
					thisSprite.y = game->player->bombSnapY;
					thisSprite.solid = false;
					bombs.push_back(thisSprite);
					PlaySound(game->sounds["place"]);
				}
			}
		}
		else if (IsKeyReleased(KEY_SPACE))
		{
			game->player->canSpawnBomb = true;
		}

	}
}

void GameStage::draw()
{

	bool collided = false;
	int collidedCount = 0;
	bool checkFloorStart = true;

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

		game->player->collidedFloors.clear();
		for (auto& it : tiles)
		{
			it.play();

			if (game->player->isCollided(it))
			{
				if (it.solid)
				{
					collided = true;
					collidedCount += 1;
					game->player->setLastCollided(it);
				}
				if(it.is_floor)
				{
					game->player->collidedFloors.push_back(it);
				}
			}
		}

		//draw bomb
		for (auto& bmb : bombs)
		{
			bmb.play();

			if (!game->player->isCollided(bmb) && !bmb.solid)
			{
				bmb.solid = true;
			}

			if (game->player->isCollided(bmb) && bmb.solid)
			{
				collided = true;
				collidedCount += 1;
				game->player->setLastCollided(bmb);
			}

			if (bmb.tickCount == 3)
			{
				//explode bomb
			}

		}

		//check where to snap the bomb
		if (game->player->collidedFloors.size() > 0)
		{
			for (auto& it : game->player->collidedFloors)
			{
				if (checkFloorStart)
				{
					checkFloorStart = false;
					game->player->bombSnapX = it.x;
					game->player->bombSnapY = it.y;
					game->player->lastOverlapRatio = game->player->getOverlapRatio(it);
					continue;
				}

				//compare lastOverlapRatio to other overlap ratio
				// if greater than last then overwrite bomb snap x/y
				float thisRatio = game->player->getOverlapRatio(it);
				if (thisRatio > game->player->lastOverlapRatio)
				{
					game->player->bombSnapX = it.x;
					game->player->bombSnapY = it.y;
					game->player->lastOverlapRatio = thisRatio;
				}
			}
		}

		game->player->collided = collided;
		game->player->collidedCount = collidedCount;

		hud->draw();

		//draw hud texts
		//DrawTextEx(GetFontDefault(), to_string(game->player->score).c_str(), (Vector2){ 30, 8 }, 10, 3, WHITE);
		DrawTextEx(GetFontDefault(), getFormattedScore(to_string(game->player->score)).c_str(), (Vector2){ 30, 8 }, 10, 3, WHITE);
		DrawTextEx(GetFontDefault(), getFormattedTime().c_str(), (Vector2){ 121, 8 }, 10, 5, WHITE);
		DrawTextEx(GetFontDefault(), to_string(game->player->lives).c_str(), (Vector2){ 185, 8 }, 10, 1.5, WHITE);
		DrawTextEx(GetFontDefault(), to_string(game->player->bombCount).c_str(), (Vector2){ 217.5, 8 }, 10, 1.5, WHITE);
		DrawTextEx(GetFontDefault(), to_string(game->player->explosionCount).c_str(), (Vector2){ 241.5, 8 }, 10, 1.5, WHITE);		
		game->player->play();

		//run timer
		timeTick();

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

void GameStage::timeTick()
{
	framesCounter++;

	if (framesCounter >= ((TARGET_FPS * 5) / FRAME_SPEED))
	{
		framesCounter = 0;

		if (timeMinutes > 0 || timeSeconds > 0)
		{
			if (timeSeconds == 0)
			{
				timeSeconds = 59;
				timeMinutes -= 1;
			}
			else
			{
				timeSeconds -= 1;
			}
		}
	}
}

string GameStage::getFormattedTime()
{

	string secStr = to_string(timeSeconds);

	if (secStr.length() == 1)
	{
		secStr = "0" + secStr;
	}

	return to_string(timeMinutes) + ":" + secStr;
}

string GameStage::getFormattedScore(string str_score)
{
	if (str_score.length() == 1)
	{
		return "0" + str_score;
	}

	return str_score;
}