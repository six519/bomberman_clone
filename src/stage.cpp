#include "stage.hpp"

Stage::Stage(Game *gm)
{
	game = gm;
	state = 0;
	initialized = false;
};

void Stage::run()
{
	if (!initialized) {
		this->init();
		initialized = true;
	}

	this->handleKeys();
	this->draw();
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
	ship->x = (game->gameWidth / 2) - (ship->getTexture().width / 2);
	ship->y = -ship->getTexture().height;
	char1->x = 8;
	char1->y = -char1->getTexture().height;
	char2->x = game->gameWidth - (char2->getTexture().width + 35);
	char2->y = game->gameHeight;
	title->x = game->gameWidth;
	title->y = 5;
	enter->x = (game->gameWidth / 2) - (enter->getTexture().width / 2);
	enter->y = 150;
}

void TitleStage::handleKeys()
{

}

void TitleStage::draw()
{
	DrawTexture(bgTitle->getTexture(), 0, 0, WHITE);
	DrawTexture(ship->getTexture(), ship->x, ship->y, WHITE);
	DrawTexture(char1->getTexture(), char1->x, char1->y, WHITE);
	DrawTexture(char2->getTexture(), char2->x, char2->y, WHITE);
	DrawTexture(title->getTexture(), title->x, title->y, WHITE);

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
		DrawTexture(enter->getTexture(), enter->x, enter->y, WHITE);
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
}

void TitleStage::cleanUp()
{
	bgTitle->unload();
	ship->unload();
	char1->unload();
	char2->unload();
	title->unload();
	enter->unload();
	UnloadMusicStream(titleMusic);
}