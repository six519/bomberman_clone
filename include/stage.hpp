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
		virtual void init()=0;
		Game *game;
		int state;
		bool initialized;
		RenderTexture2D renderTexture;
		int width;
		int height;
	public:
		Stage(Game *gm, int width, int height);
		void run();
		virtual void cleanUp()=0;
};

class TitleStage: public Stage {
	using Stage::Stage;
	protected:
		void handleKeys();
		void draw();
		void init();
	private:
		Sprite *bgTitle;
		Sprite *ship;
		Sprite *char1;
		Sprite *char2;
		Sprite *title;
		Sprite *enter;
		Music titleMusic;
	public:
		void cleanUp();
};

#endif