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
}

void TitleStage::handleKeys()
{

}

void TitleStage::draw()
{
	DrawTexture(bgTitle->getTexture(), 0, 0, WHITE);
}

void TitleStage::cleanUp()
{
	bgTitle->unload();
}