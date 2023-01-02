#include "sprite.hpp"

Sprite::Sprite(string imagePath)
{
	texture = LoadTexture(imagePath.c_str());
	x = 0;
	y = 0;
}

Sprite::Sprite()
{
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

void Sprite::setTexture(Texture2D texture)
{
	this->texture = texture;
}