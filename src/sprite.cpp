#include "sprite.hpp"
#include "settings.hpp"

Sprite::Sprite(string imagePath)
{
	texture = LoadTexture(imagePath.c_str());
	x = 0;
	y = 0;
	currentFrame = 0;
	framesCounter = 0;
	tileCount = 0;
	stopped = false;
}

Sprite::Sprite()
{
	x = 0;
	y = 0;
	currentFrame = 0;
	framesCounter = 0;
	tileCount = 0;
	stopped = false;
}

Sprite::Sprite(string imagePath, int tileCount)
{
	texture = LoadTexture(imagePath.c_str());
	x = 0;
	y = 0;
	currentFrame = 0;
	framesCounter = 0;
	this->tileCount = tileCount;
	frameRec = (Rectangle){ 0.0, 0.0, (float)texture.width/tileCount, (float)texture.height };
	stopped = false;
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

void Sprite::play()
{
	if (tileCount > 0)
	{

		if (!stopped)
		{
			framesCounter++;

			if (framesCounter >= (TARGET_FPS / FRAME_SPEED))
			{
				framesCounter = 0;
				currentFrame++;

				if (currentFrame > (tileCount - 1))
					currentFrame = 0;

				frameRec.x = (float)currentFrame*(float)texture.width/tileCount;
			}
		}

		DrawTextureRec(texture, frameRec, (Vector2){ (float)x,(float)y }, WHITE);
	}
}