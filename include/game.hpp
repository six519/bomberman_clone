#ifndef _GAME_H_
#define _GAME_H_
#include <string>
#include <vector>
#include <map>
#include <raylib.h>
#include "sprite.hpp"
#include "stage.hpp"
#include "levels.hpp"
#include "settings.hpp"
#include "player.hpp"
#include "breakables.hpp"

#define CASTLE_TEXTURE_COUNT 60
#define CASTLE_TEXTURE_PATH "castle/"
#define CASTLE_FNAME_PREFIX "c"

using namespace std;

class TitleStage;
class GameStage;

class Game
{
	private:
		string title;
		TitleStage *titleStage;
		GameStage *levelOne;
		void cleanUp();
		void loadTextures(int count, string path, string prefix);
		void unloadTextures();
		void loadSound(string path, string name);
		void unloadSounds();
	public:
		int screenWidth;
		int screenHeight;
		int gameWidth;
		int gameHeight;
		int state;
		Music stageStart;
		Music bgm1;
		map<string, Texture2D> textures;
		map<string, Sound> sounds;
		Player *player;
		Game(string t, int sw, int sh, int gw, int gh, int fps);
		void run();
};

#endif