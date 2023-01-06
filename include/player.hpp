#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <string>
#include <raylib.h>

using namespace std;

class Player
{
	private:
	public:
		int x;
		int y;
		Player();
		void unload();
		void play();
};

#endif