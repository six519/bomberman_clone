#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "sprite.hpp"
#include <string>
#include <algorithm> 
#include <raylib.h>

#define PLAYER_DOWN 0
#define PLAYER_UP 1
#define PLAYER_LEFT 2
#define PLAYER_RIGHT 3
#define PLAYER_WALK_DOWN 4
#define PLAYER_WALK_UP 5
#define PLAYER_WALK_LEFT 6
#define PLAYER_WALK_RIGHT 7

#define PLAYER_SPEED 1
#define PLAYER_FRAME_SPEED 38

using namespace std;

class Player
{
	private:
		Sprite *up;
		Sprite *down;
		Sprite *left;
		Sprite *right;
	public:
		int x;
		int y;
		int currentMovement;
		int lastMovement;
		bool collided;
		bool canSpawnBomb;
		Player();
		void unload();
		void play();
		bool isCollided(Sprite& s);
		bool isCollidedWithNotSolidBombs(vector<BombSprite> bombs);
		void setLastCollided(Sprite& s);
		int framesCounter;
		int collidedCount;
		int lastCollidedX;
		int lastCollidedY;
		int bombSnapX;
		int bombSnapY;
		int bombCount;
		int lives;
		int explosionCount;
		float lastOverlapRatio;
		vector<Sprite> collidedFloors;
		float getOverlapRatio(Sprite s);
};

#endif