#include "Player.h"


Player::Player() : gameObject()
{
	upPressed = rightPressed = downPressed = leftPressed = leftShiftPressed = false;
}

Player::Player(Vector2f position, Vector2f size, Texture* texture, float speed) : gameObject(position, size, texture, speed)
{
	upPressed = rightPressed = downPressed = leftPressed = leftShiftPressed = false;
	body.setOutlineThickness(0);
	body.setFillColor(Color::White);
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


