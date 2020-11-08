#include "Player.h"




Player::Player() :Entity()
{
	upPressed = rightPressed = downPressed = leftPressed = false;
}

Player::Player(float xsize, float ysize, float xpos, float ypos, float speed) :Entity(xsize, ysize, xpos, ypos, speed)
{
	upPressed = rightPressed = downPressed = leftPressed = false;
}

//Update state 
void Player::update()
{
	if (upPressed)
		body.move(0, -basespeed);
	if (rightPressed)
		body.move(basespeed, 0);
	if (downPressed)
		body.move(0, basespeed);
	if (leftPressed)
		body.move(-basespeed, 0);
}

//Update state time-based
void Player::update(int)
{
	if (upPressed)
		body.move(0, -speed);
	if (rightPressed)
		body.move(speed, 0);
	if (downPressed)
		body.move(0, speed);
	if (leftPressed)
		body.move(-speed, 0);
}

Vector2f Player::getcenter()
{
	return Vector2f(body.getPosition() + body.getSize() / 2.f);
}