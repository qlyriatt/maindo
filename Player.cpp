#include "Player.h"


Player::Player() : gameObject()
{
	upPressed = rightPressed = downPressed = leftPressed = leftShiftPressed = false;
	overrideVector = Vector2f(0, 0);
}

Player::Player(Vector2f position, Vector2f size, Texture* texture, float speed) : gameObject(position, size, texture, speed)
{
	upPressed = rightPressed = downPressed = leftPressed = leftShiftPressed = false;
	overrideVector = Vector2f(0, 0);
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
	if (leftShiftPressed)
		speed = baseSpeed / 2;
	else
		speed = baseSpeed;
	pendingDirection = currentDirection = Vector2f(x, y);

	if (overrideVector.x)
		currentDirection.x = 0;
	else if (overrideVector.y)
		currentDirection.y = 0;

	if (currentDirection != Vector2f(0, 0))
	{
		currentSight = currentDirection;
	}

	gameObject::updatePosition(elapsedTime);
}

bool Player::checkPending(gameObject obstacle)
{
	if (obstacle.body.getGlobalBounds().intersects(body.getGlobalBounds()) and (pendingDirection.x and pendingDirection.y) and !obstacle.allowCollision)
	{
		return true;
	}
	return false;
}

bool Player::collisionCheck(gameObject obstacle, bool* needOverride)
{
	if (obstacle.body.getGlobalBounds().intersects(body.getGlobalBounds()))
	{
		if (obstacle.allowCollision)
			return true;

		if (pendingDirection.x and pendingDirection.y and needOverride)
			*needOverride = true;

		if (!(currentDirection.x and currentDirection.y))
		{
			body.move(-currentDirection * latestDistanceCovered);
			return true;
		}

		const Vector2f UP = Vector2f(0, -1);
		const Vector2f RIGHT = Vector2f(1, 0);
		const Vector2f DOWN = -UP;
		const Vector2f LEFT = -RIGHT;

		if (currentDirection == UP + RIGHT)
		{
			body.move(latestDistanceCovered * LEFT);
			if (obstacle.body.getGlobalBounds().intersects(body.getGlobalBounds()))
			{
				body.move(latestDistanceCovered * (RIGHT + DOWN));
				overrideVector = UP; //upPressed = false;
			}
			else
				overrideVector = RIGHT; //rightPressed = false;
		}

		else if (currentDirection == UP + LEFT)
		{
			body.move(latestDistanceCovered * RIGHT);
			if (obstacle.body.getGlobalBounds().intersects(body.getGlobalBounds()))
			{
				body.move(latestDistanceCovered * (LEFT + DOWN));
				overrideVector = UP; //upPressed = false;
			}
			else
				overrideVector = LEFT; //leftPressed = false;
		}

		else if (currentDirection == DOWN + RIGHT)
		{
			body.move(latestDistanceCovered * LEFT);
			if (obstacle.body.getGlobalBounds().intersects(body.getGlobalBounds()))
			{
				body.move(latestDistanceCovered * (RIGHT + UP));
				overrideVector = DOWN; //downPressed = false;
			}
			else
				overrideVector = RIGHT; //rightPressed = false;
		}

		else if (currentDirection == DOWN + LEFT)
		{
			body.move(latestDistanceCovered * RIGHT);
			if (obstacle.body.getGlobalBounds().intersects(body.getGlobalBounds()))
			{
				body.move(latestDistanceCovered * (LEFT + UP));
				overrideVector = DOWN; //downPressed = false;
			}
			else
				overrideVector = LEFT; //leftPressed = false;
		}
		return true;
	}
	return false;
}

bool Player::interactionCheck(gameObject object)
{
	const Vector2f interactionRadius = Vector2f(object.interactionRadius, object.interactionRadius);
	
	FloatRect interactionZone(object.body.getPosition() - interactionRadius, object.body.getSize() + 2.f * interactionRadius);
	
	return gameObject::collisionCheck(interactionZone);
}

void Player::collisionCheckInner(FloatRect area)
{
	bool TL = area.contains(body.getPosition());
	bool TR = area.contains(body.getPosition() + Vector2f(body.getGlobalBounds().width, 0));
	bool BL = area.contains(body.getPosition() + Vector2f(0, body.getGlobalBounds().height));
	bool BR = area.contains(body.getPosition() + Vector2f(body.getGlobalBounds().width, body.getGlobalBounds().height));
	Vector2f solution(0, 0);
	
	if (!(TL and TR and BR and BL))
	{
		if (TL)
		{
			if (BL)
				solution = Vector2f(-1, 0);
			else if (TR)
				solution = Vector2f(0, -1);
			else
				solution = Vector2f(-1, -1);
		}

		else if (BR)
		{
			if (TR)
				solution = Vector2f(1, 0);
			else if (BL)
				solution = Vector2f(0, 1);
			else
				solution = Vector2f(1, 1);
		}

		else if (BL)
			solution = Vector2f(-1, 1);
		else if (TR)
			solution = Vector2f(1, -1);

		body.move(latestDistanceCovered * solution);
	}

}

