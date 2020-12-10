#include "Player.h"
#include <iostream>

Player::Player() : gameObject()
{
	upPressed = rightPressed = downPressed = leftPressed = leftShiftPressed = false;
	overrideInputX = overrideInputY = isSetIdle = isUsingWeapon = isInventoryOpen = false;
	animationCycleTimer = latestAnimationUpdate = latestAnimationType = 0;
}

Player::Player(Vector2f position, Vector2f size, Texture* texture, float speed) : gameObject(position, size, texture, speed)
{
	upPressed = rightPressed = downPressed = leftPressed = leftShiftPressed = false;
	overrideInputX = overrideInputY = isSetIdle = isUsingWeapon = isInventoryOpen = false;
	animationCycleTimer = latestAnimationUpdate = latestAnimationType = 0;
	isAnimated = true;


	body.setOutlineThickness(0);
	body.setFillColor(Color::White);

	inventorySlots.resize(8);
	inventorySlots = { 0,0,0,0,0,0,0,0 };
}

void Player::updatePosition(float elapsedTime)
{
	float x = 0, y = 0;
	if (upPressed) y--;
	if (downPressed) y++;
	if (rightPressed) x++;
	if (leftPressed) x--;
	speed = leftShiftPressed ? baseSpeed / 2 : baseSpeed;

	pendingDirection = currentDirection = Vector2f(x, y);

	if (overrideInputX)
		currentDirection.x = 0;
	else if (overrideInputY)
		currentDirection.y = 0;

	if (currentDirection != Vector2f(0, 0))
		currentSight = currentDirection;

	gameObject::updatePosition(elapsedTime);
}

void Player::updateAnimation(float elapsedTime, const Texture* texture)
{
	const int DOWN = 0;
	const int UP = 1;
	const int LEFT = 2;
	const int RIGHT = 3;
	int animationStates = 4; //for now

	if (isUsingWeapon)
	{
		if (!latestAnimationUpdate) //skips 1 frame of lAU == 0
		{
			latestAnimationUpdate = elapsedTime;
			return;
		}
		if (latestAnimationType != animationStates::usingWeapon) //skips 1 frame of wrong animation type
		{
			latestAnimationType = animationStates::usingWeapon;
			animationCycleTimer = 0;
			return;
		}
		if (weapon.isMelee and animationCycleTimer > weapon.projectileLifetime) //restores state after melee swing
		{
			animationCycleTimer = 0;
			isUsingWeapon = false;
			return;
		}

		isSetIdle = false;

		//doubles animation speed
		int x = int(animationCycleTimer * animationStates * 2) % animationStates; 

		sprite.setTextureRect(IntRect(Vector2i(weapon.actionSpriteSize.x * x, 4 * body.getSize().y), weapon.actionSpriteSize));
		sprite.setPosition(body.getPosition() - Vector2f(weapon.actionSpriteOffset));
	}

	else if (isMoving)
	{
		if (!latestAnimationUpdate) //skips 1 frame of lAU == 0
		{
			latestAnimationUpdate = elapsedTime;
			return;
		}
		if (latestAnimationType != animationStates::moving) //skips 1 frame of wrong animation type
		{
			latestAnimationType = animationStates::moving;
			animationCycleTimer = 0;
			return;
		}

		isSetIdle = false;
		if (previousFrameDirection != currentDirection)	//resets animation when direction is changed
			animationCycleTimer = 0;

		int x = int(animationCycleTimer * animationStates) % animationStates;
		int y = 0;

		//prefers X over Y
		if (currentDirection.x == 1)		y = RIGHT;
		else if (currentDirection.x == -1)	y = LEFT;
		else if (currentDirection.y == 1)	y = DOWN;
		else if (currentDirection.y == -1)	y = UP;


		sprite.setTextureRect(IntRect(Vector2i(body.getSize().x * x, body.getSize().y * y), Vector2i(body.getSize())));
		sprite.setPosition(body.getPosition());
		previousFrameDirection = currentDirection;
	}

	else if(!isSetIdle)	//skips animation update when nothing of the above is present <----> should not be here for long
	{
		latestAnimationType = animationStates::idle;
		animationCycleTimer = latestAnimationUpdate = 0;
		previousFrameDirection = Vector2f(0, 0);

		if (currentSight.y == 1)
			sprite.setTextureRect(IntRect(Vector2i(0, DOWN * body.getSize().y), Vector2i(body.getSize())));
		else if (currentSight.y == -1)
			sprite.setTextureRect(IntRect(Vector2i(0, UP * body.getSize().y), Vector2i(body.getSize())));
		else if (currentSight.x == -1)
			sprite.setTextureRect(IntRect(Vector2i(0, LEFT * body.getSize().y), Vector2i(body.getSize())));
		else if (currentSight.x == 1)
			sprite.setTextureRect(IntRect(Vector2i(0, RIGHT * body.getSize().y), Vector2i(body.getSize())));

		sprite.setPosition(body.getPosition());
		isSetIdle = true;

		return;
	}

	animationCycleTimer += elapsedTime - latestAnimationUpdate;
	latestAnimationUpdate = elapsedTime;
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
		if (obstacle.body.getGlobalBounds().intersects(body.getGlobalBounds()) and needOverride /*tmp workaround*/)
			*needOverride = true; //caused nullptr twice
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

