#include "sprite.hpp"
#include "settings.hpp"

Sprite::Sprite(string imagePath)
{
	texture = LoadTexture(imagePath.c_str());
	x = 0;
	y = 0;
	currentFrame = 0;
	framesCounter = 0;
	speedCounter = 0;
	tileCount = 0;
	stopped = false;
	solid = true;
	moveSpeed = 1;
	moveAmount = 1;
	lootSprite = NULL;
	backSprite = NULL;
}

Sprite::Sprite()
{
	x = 0;
	y = 0;
	currentFrame = 0;
	framesCounter = 0;
	speedCounter = 0;
	tileCount = 0;
	stopped = false;
	solid = true;
	moveSpeed = 1;
	moveAmount = 1;
	lootSprite = NULL;
	backSprite = NULL;
}

Sprite::Sprite(string imagePath, int tileCount)
{
	texture = LoadTexture(imagePath.c_str());
	x = 0;
	y = 0;
	currentFrame = 0;
	framesCounter = 0;
	speedCounter = 0;
	this->tileCount = tileCount;
	frameRec = (Rectangle){ 0.0, 0.0, (float)texture.width/tileCount, (float)texture.height };
	stopped = false;
	solid = true;
	moveSpeed = 1;
	moveAmount = 1;
	lootSprite = NULL;
	backSprite = NULL;
}

Sprite::Sprite(int tileCount)
{
	x = 0;
	y = 0;
	currentFrame = 0;
	framesCounter = 0;
	speedCounter = 0;
	this->tileCount = tileCount;
	stopped = false;
	solid = true;
	moveSpeed = 1;
	moveAmount = 1;
	lootSprite = NULL;
	backSprite = NULL;
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
	frameRec = (Rectangle){ 0.0, 0.0, (float)texture.width/tileCount, (float)texture.height };
}

void Sprite::draw()
{
	DrawTexture(texture, x, y, WHITE);
}

void Sprite::playIndex(int ind)
{
	frameRec.x = (float)ind*(float)texture.width/tileCount;
	DrawTextureRec(texture, frameRec, (Vector2){ (float)x,(float)y }, WHITE);
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

void Sprite::setMoveAmount(int a)
{
	moveAmount = a;
}

void Sprite::move(int m)
{
	speedCounter++;

	if (speedCounter >= (TARGET_FPS / moveSpeed))
	{

		switch (m)
		{
		case SPRITE_MOVE_DOWN:
			this->y += moveAmount;
			break;
		case SPRITE_MOVE_LEFT:
			this->x -= moveAmount;
			break;
		case SPRITE_MOVE_RIGHT:
			this->x += moveAmount;
			break;
		default:
			this->y -= moveAmount;
			break;
		}

		speedCounter = 0;
	}
}

void Sprite::moveDown()
{
	move(SPRITE_MOVE_DOWN);
}

void Sprite::moveUp()
{
	move(SPRITE_MOVE_UP);
}

void Sprite::moveLeft()
{
	move(SPRITE_MOVE_LEFT);
}

void Sprite::moveRight()
{
	move(SPRITE_MOVE_RIGHT);
}

void Sprite::setMoveSpeed(int speed)
{
	moveSpeed = speed;
}