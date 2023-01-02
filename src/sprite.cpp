#include "sprite.hpp"

Sprite::Sprite(string imagePath)
{
	texture = LoadTexture(imagePath.c_str());
	width = texture.width;
	height = texture.height;
	x = 0;
	y = 0;
}

void Sprite::unload()
{
	UnloadTexture(texture);
}

Texture2D Sprite::getTexture()
{
	return texture;
}