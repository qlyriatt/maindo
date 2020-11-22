#include "Player.h"


Player::Player() : gameObject()
{
	upPressed = rightPressed = downPressed = leftPressed = leftShiftPressed = false;
}

Player::Player(float speed, Vector2f position, Texture* texture) : gameObject(speed, position, texture)
{
	upPressed = rightPressed = downPressed = leftPressed = leftShiftPressed = false;
}

void Player::updatePosition(float elapsedTime)
{
	float x = 0, y = 0;
	if (upPressed)
		y--;
	if (downPressed)
		y++;
	if (rightPressed)
		x++;
	if (leftPressed)
		x--;

	currentDirection = Vector2f(x, y);
	if (currentDirection != Vector2f(0, 0))
	{
		currentSight = currentDirection;
	}


	gameObject::updatePosition(elapsedTime);
}


