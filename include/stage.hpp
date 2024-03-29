#ifndef _STAGE_H_
#define _STAGE_H_
#include "game.hpp"
#include "player.hpp"
#include <iostream>
#include <vector>
#include <map>

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
		Sprite *bomb;
		Music titleMusic;
	public:
		void cleanUp();
};

class GameStage: public Stage {
	using Stage::Stage;
	protected:
		void handleKeys();
		void draw();
		void init();
		vector<Sprite> tiles;
		vector<BombSprite> bombs;
		Sprite *hud;
		string title;
		int txtX;
		int showCounter;
		Vector2 txtVec;
		Music currentBg;
		void playerMove(int move);
		void slideUporDown();
		void slideLeftorRight();
	public:
		int timeSeconds;
		int timeMinutes;
		int framesCounter;
		GameStage(Game *gm, int width, int height, vector<vector <string>> level, map<string,string> breakable, string title, Music bg, int px, int py);
		void cleanUp();
		void timeTick();
		string getFormattedTime();
		string getFormattedScore(string str_score);
};

/*
class TestStage: public GameStage{
	using GameStage::GameStage;
	protected:
		void handleKeys(){};
		void draw(){
			cout << "draw\n";
		};
		void init(){};

	public:
		void cleanUp(){};
};
*/

#endif