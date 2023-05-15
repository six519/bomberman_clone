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
	protected:
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
		Sprite *lootSprite;
		Sprite *backSprite;
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
		bool is_floor;
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		void setMoveSpeed(int speed);
		void setMoveAmount(int a);
		virtual void onLastFrame();
};

class BombSprite: public Sprite 
{
	using Sprite::Sprite;
	public:
		int tickCount;
		BombSprite();
		void onLastFrame() override;
};

#endif