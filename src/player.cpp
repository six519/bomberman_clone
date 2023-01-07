#include "player.hpp"

Player::Player()
{
	currentMovement = PLAYER_DOWN;
	x = 0;
	y = 0;

	up = new Sprite("assets/u.png", 4);
	down = new Sprite("assets/d.png", 4);
	left = new Sprite("assets/l.png", 4);
	right = new Sprite("assets/r.png", 4);
}

void Player::unload()
{
	up->unload();
	down->unload();
	left->unload();
	right->unload();
}

void Player::play()
{
	switch (currentMovement)
	{
	case PLAYER_LEFT:
		left->x = x;
		left->y = y;
		left->playIndex(0);
		break;
	case PLAYER_RIGHT:
		right->x = x;
		right->y = y;
		right->playIndex(0);
		break;
	case PLAYER_UP:
		up->x = x;
		up->y = y;
		up->playIndex(0);
		break;
	case PLAYER_WALK_DOWN:
		down->x = x;
		down->y = y;
		down->play();
		break;
	case PLAYER_WALK_LEFT:
		left->x = x;
		left->y = y;
		left->play();
		break;
	case PLAYER_WALK_RIGHT:
		right->x = x;
		right->y = y;
		right->play();
		break;
	case PLAYER_WALK_UP:
		up->x = x;
		up->y = y;
		up->play();
		break;
	default:
		//PLAYER_DOWN
		down->x = x;
		down->y = y;
		down->playIndex(0);
		break;
	}
}

bool Player::isCollided(Sprite s)
{

	if (!s.solid)
		return false;

	int lowerX1 = this->x + 15 - 1;
	int lowerY1 = (this->y + 16) + 16 - 1; //bottom part of player
	int lowerX2 = s.x + s.getTexture().width - 2;
	int lowerY2 = s.y + s.getTexture().height - 1;

	if (lowerX1 < s.x || this->x > lowerX2 || lowerY1 < s.y || (this->y + 16) > lowerY2) 
	{
		return false;
	}

	return true;
}