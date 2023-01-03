#include "sprite.hpp"

Sprite::Sprite(string imagePath)
{
	texture = LoadTexture(imagePath.c_str());
	x = 0;
	y = 0;
	currentFrame = 0;
	framesCounter = 0;
	tileCount = 0;
}

Sprite::Sprite()
{
	x = 0;
	y = 0;
	currentFrame = 0;
	framesCounter = 0;
	tileCount = 0;
}

Sprite::Sprite(string imagePath, int tileCount)
{
	texture = LoadTexture(imagePath.c_str());
	x = 0;
	y = 0;
	currentFrame = 0;
	framesCounter = 0;
	this->tileCount = tileCount;
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

void Sprite::draw()
{
	DrawTexture(texture, x, y, WHITE);
}