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