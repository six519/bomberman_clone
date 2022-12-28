#ifndef _STAGE_H_
#define _STAGE_H_
#include "game.hpp"
#include <iostream>

using namespace std;

class Game;

class Stage
{
	protected:
		virtual void handleKeys()=0;
		virtual void draw()=0;
		Game *game;
	public:
		Stage(Game *gm);
		void run();
};

class TitleStage: public Stage {
	using Stage::Stage;
	protected:
		void handleKeys();
		void draw();
};

#endif