#include "stage.hpp"

Stage::Stage(Game *gm)
{
	game = gm;
};

void Stage::run()
{
	this->handleKeys();
	this->draw();
}


void TitleStage::handleKeys()
{

}

void TitleStage::draw()
{
	DrawTexture(game->bgTitle->getTexture(), 0, 0, WHITE);
}