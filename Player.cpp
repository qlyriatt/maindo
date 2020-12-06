#include "Player.h"
#include <iostream>
using namespace std;

Player::Player() : gameObject()
{
	upPressed = rightPressed = downPressed = leftPressed = leftShiftPressed = false;
	overrideInputX = overrideInputY = isSetIdle = isUsingWeapon = false;
	animationCycleTimer = latestAnimationUpdate = 0;
}

Player::Player(Vector2f position, Vector2f size, Texture* texture, float speed) : gameObject(position, size, texture, speed)
{
	upPressed = rightPressed = downPressed = leftPressed = leftShiftPressed = false;
	overrideInputX = overrideInputY = false;
	body.setOutlineThickness(0);
	body.setFillColor(Color::White);
	animated = true;
	animationCycleTimer = 0;
	isSetIdle = false;
	isUsingWeapon = false;
	latestAnimationUpdate = 0;
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

	if (overrideInputX)
		currentDirection.x = 0;
	else if (overrideInputY)
		currentDirection.y = 0;

	if (currentDirection != Vector2f(0, 0))
	{
		currentSight = currentDirection;
	}

	gameObject::updatePosition(elapsedTime);
}

void Player::updateAnimation(float elapsedTime, const Texture* texture)
{
	
	int animationStates = 4; //for now

	if (isUsingWeapon)
	{
		if (!latestAnimationUpdate)
		{
			latestAnimationUpdate = elapsedTime;
			return;
		}
		if (latestAnimationType != 2)
		{
			latestAnimationType = 2;
			animationCycleTimer = 0;
			return;
		}
		if (weapon.isMelee and animationCycleTimer > weapon.projectileLifetime)
		{
			isUsingWeapon = false;
			return;
		}
		animationStates *= 2;
		int x = int(floor(animationCycleTimer * animationStates)) % animationStates % animationStates;


		isSetIdle = false;

		IntRect neededTextureRect(Vector2i(weapon.actionSpriteSize.x * x, 4 * body.getSize().y), weapon.actionSpriteSize);
		sprite.setTextureRect(neededTextureRect);
		sprite.setPosition(body.getPosition() - Vector2f(weapon.actionSpriteOffset));

		animationCycleTimer += elapsedTime - latestAnimationUpdate;
		latestAnimationUpdate = elapsedTime;
	}
	else if (isMoving)
	{
		if (!latestAnimationUpdate)
		{
			latestAnimationUpdate = elapsedTime;
			return;
		}
		if (latestAnimationType != 1)
		{
			latestAnimationType = 1;
			animationCycleTimer = 0;
			return;
		}

		isSetIdle = false;
		if (previousFrameDirection != currentDirection)
			animationCycleTimer = 0;

		int x = int(floor(animationCycleTimer * animationStates)) % animationStates;
		int y = 0;

		//prefers X over Y
		if (currentDirection.x == 1)
			y = 3;
		else if (currentDirection.x == -1)
			y = 2;
		else if (currentDirection.y == 1)
			y = 0;
		else if (currentDirection.y == -1)
			y = 1;

		//body.setTextureRect(IntRect(Vector2i(body.getSize().x * x, body.getSize().y * y), Vector2i(body.getSize())));
		sprite.setTextureRect(IntRect(Vector2i(body.getSize().x * x, body.getSize().y * y), Vector2i(body.getSize())));
		sprite.setPosition(body.getPosition());

		animationCycleTimer += elapsedTime - latestAnimationUpdate;
		latestAnimationUpdate = elapsedTime;
		previousFrameDirection = currentDirection;
	}
	else if(!isSetIdle)
	{
		latestAnimationType = 0;
		animationCycleTimer = latestAnimationUpdate = 0;
		previousFrameDirection = Vector2f(0, 0);

		if (currentSight.y == 1)
			sprite.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(body.getSize())));
		else if (currentSight.y == -1)
			sprite.setTextureRect(IntRect(Vector2i(0, body.getSize().y), Vector2i(body.getSize())));
		else if (currentSight.x == -1)
			sprite.setTextureRect(IntRect(Vector2i(0, 2 * body.getSize().y), Vector2i(body.getSize())));
		else if (currentSight.x == 1)
			sprite.setTextureRect(IntRect(Vector2i(0, 3 * body.getSize().y), Vector2i(body.getSize())));

		isSetIdle = true;
	}

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
				overrideInputY = true; //upPressed = false;
			}
			else
				overrideInputX = true; //rightPressed = false;
		}

		else if (currentDirection == UP + LEFT)
		{
			body.move(latestDistanceCovered * RIGHT);
			if (obstacle.body.getGlobalBounds().intersects(body.getGlobalBounds()))
			{
				body.move(latestDistanceCovered * (LEFT + DOWN));
				overrideInputY = true; //upPressed = false;
			}
			else
				overrideInputX = true; //leftPressed = false;
		}

		else if (currentDirection == DOWN + RIGHT)
		{
			body.move(latestDistanceCovered * LEFT);
			if (obstacle.body.getGlobalBounds().intersects(body.getGlobalBounds()))
			{
				body.move(latestDistanceCovered * (RIGHT + UP));
				overrideInputY = true; //downPressed = false;
			}
			else
				overrideInputX = true; //rightPressed = false;
		}

		else if (currentDirection == DOWN + LEFT)
		{
			body.move(latestDistanceCovered * RIGHT);
			if (obstacle.body.getGlobalBounds().intersects(body.getGlobalBounds()))
			{
				body.move(latestDistanceCovered * (LEFT + UP));
				overrideInputY = true; //downPressed = false;
			}
			else
				overrideInputX = true; //leftPressed = false;
		}
		return true;
	}
	else if ((overrideInputX or overrideInputY) and currentDirection != Vector2f(0,0))
	{
		Vector2f pendingCheck((pendingDirection - currentDirection) * latestDistanceCovered);
		body.move(pendingCheck);
		if (obstacle.body.getGlobalBounds().intersects(body.getGlobalBounds()))
			*needOverride = true; //caused nullptr
		body.move(-pendingCheck);
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

