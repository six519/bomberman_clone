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
	ship->x = (game->gameWidth / 2) - (ship->getTexture().width / 2);
	ship->y = -ship->getTexture().height;
}

void TitleStage::handleKeys()
{

}

void TitleStage::draw()
{
	DrawTexture(bgTitle->getTexture(), 0, 0, WHITE);
	DrawTexture(ship->getTexture(), ship->x, ship->y, WHITE);

	switch (state)
	{
	case 1:
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
}