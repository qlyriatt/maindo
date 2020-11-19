#include "Player.h"


Player::Player() :gameObject()
{
	upPressed = rightPressed = downPressed = leftPressed = moving = leftShiftPressed = false;
}

Player::Player(float speed, Vector2f position, Texture* texture) : gameObject(speed, position, texture)
{
	upPressed = rightPressed = downPressed = leftPressed = leftShiftPressed = moving = false;
}

Vector2f Player::getdirection()
{
	float x, y;
	x = y = 0;

	if (upPressed)
		y--;
	if (rightPressed)
		x++;
	if (downPressed)
		y++;
	if (leftPressed)
		x--;

	return Vector2f(x, y);
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
	{
		body.move(0, -speed);
		sprite.move(0, -speed);
	}
	if (rightPressed)
	{
		body.move(speed, 0);
		sprite.move(speed, 0);
	}
	if (downPressed)
	{
		body.move(0, speed);
		sprite.move(0, speed);
	}
	if (leftPressed)
	{
		body.move(-speed, 0);
		sprite.move(-speed, 0);
	}
}

void Player::blink()
{
	//float blinkconst = 0.0375 / speed;   0.15 SPEED = 0.25 BLINKCONST
	float blinkconst = 0.25;

	if (upPressed or rightPressed or downPressed or leftPressed)
	{
		if (!moving)
		{
			moving = true;
			clock.restart();
		}


		if (leftShiftPressed)
		{
			blinkconst = 0.5;
		}

		int timepassed = int(trunc(clock.getElapsedTime().asSeconds() / blinkconst));

		if (timepassed % 2 == 1)
		{
			body.setFillColor(Color(0, 0, 255));
		}
		else
			body.setFillColor(Color(255, 255, 255));
	}

	else
	{
		body.setFillColor(Color(255, 255, 255));
		moving = false;
	}
}

