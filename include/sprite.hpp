#ifndef _SPRITE_H_
#define _SPRITE_H_
#include <string>
#include <raylib.h>

using namespace std;

class Sprite
{
	private:
		Texture2D texture;
		int currentFrame;
		int framesCounter;
		int tileCount;
	public:
		int x;
		int y;
		Sprite(string imagePath);
		Sprite();
		Sprite(string imagePath, int tileCount);
		void unload();
		Texture2D getTexture();
		void setTexture(Texture2D texture);
		void draw();
};

#endif