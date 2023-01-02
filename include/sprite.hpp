#ifndef _SPRITE_H_
#define _SPRITE_H_
#include <string>
#include <raylib.h>

using namespace std;

class Sprite
{
	private:
		Texture2D texture;
	public:
		int width;
		int height;
		int x;
		int y;
		Sprite(string imagePath);
		void unload();
		Texture2D getTexture();
};

#endif