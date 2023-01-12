#ifndef _SPRITE_H_
#define _SPRITE_H_
#include <string>
#include <raylib.h>

#define SPRITE_MOVE_UP 0
#define SPRITE_MOVE_DOWN 1
#define SPRITE_MOVE_LEFT 2
#define SPRITE_MOVE_RIGHT 3

using namespace std;

class Sprite
{
	private:
		Texture2D texture;
		int currentFrame;
		int framesCounter;
		int speedCounter;
		int tileCount;
		Rectangle frameRec;
		bool stopped;
		int moveSpeed;
		int moveAmount;
		void move(int m);
	public:
		int x;
		int y;
		Sprite(string imagePath);
		Sprite();
		Sprite(string imagePath, int tileCount);
		Sprite(int tileCount);
		void unload();
		Texture2D getTexture();
		void setTexture(Texture2D texture);
		void draw();
		void play();
		void playIndex(int ind);
		bool solid;
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		void setMoveSpeed(int speed);
		void setMoveAmount(int a);
};

#endif