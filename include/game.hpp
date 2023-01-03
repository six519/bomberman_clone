#ifndef _GAME_H_
#define _GAME_H_
#include <string>
#include <vector>
#include "sprite.hpp"
#include "stage.hpp"

using namespace std;

class TitleStage;

class Game
{
	private:
		string title;
		TitleStage *titleStage;
		void cleanUp();
	public:
		int screenWidth;
		int screenHeight;
		int gameWidth;
		int gameHeight;
		int state;
		Game(string t, int sw, int sh, int gw, int gh, int fps);
		void run();
};

#endif