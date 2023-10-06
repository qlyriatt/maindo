#include "Player.h"

#include "SFML/Window/Keyboard.hpp"

#include <iostream>

#pragma GCC diagnostic ignored "-Wnarrowing"

using sf::Keyboard;
// Player::Player(const Vector2f& position, const Vector2f& size, const Texture& texture, const size_t animationStates, const float speed) :
// 	gameObject(position, texture, animationStates, speed, false, false, 0, 0, 0)
// {
// 	body.setSize(size);
// 	sprite.setTextureRect(IntRect(Vector2i{ 0,0 }, Vector2i{ body.getSize() }));
// }

void Player::applyKeyboardInput()
{
    int x = 0, y = 0;
    
    // remember that up is -Y and down is +Y
    if (Keyboard::isKeyPressed(Keyboard::W)) y--;
    if (Keyboard::isKeyPressed(Keyboard::S)) y++;
    //
    if (Keyboard::isKeyPressed(Keyboard::D)) x++;
    if (Keyboard::isKeyPressed(Keyboard::A)) x--;

    currentDirection = {x, y};
    //currentSight = x or y ? Vector2f{x, y} : Vector2f {1, 0};
    x or y ? currentSight = {x, y} : currentSight = {1, 0};
    x or y ? isMoving = true : isMoving = false;
    x or y ? currentSpeed = 500 : currentSpeed = 0;
}

void Player::updatePosition(float elapsedTime)
{
    applyKeyboardInput();
    MovingObject::updatePosition(elapsedTime);
	//speed = leftShiftPressed ? basespeed / 2 : basespeed;

	// if (overrideInputX)
	// 	currentDirection.x = 0;
	// else if (overrideInputY)
	// 	currentDirection.y = 0;

	// if (currentDirection != Vector2f(0, 0))
	// 	currentSight = currentDirection;

	// MovingObject::updatePosition(elapsedTime);
}


// void Player::updateAnimation(float elapsedTime, const Texture* texture)
// {
// 	const int RIGHT = 0;
// 	const int LEFT = 1;
// 	const int DOWN = 2;
// 	const int UP = 3;
// 	int animationStates = 6; //for now

// 	if (isUsingWeapon)
// 	{
// 		if (!latestAnimationUpdate) //skips 1 frame of lAU == 0
// 		{
// 			latestAnimationUpdate = elapsedTime;
// 			return;
// 		}
// 		if (latestAnimationType != animationStates::usingWeapon) //skips 1 frame of wrong animation type
// 		{
// 			latestAnimationType = animationStates::usingWeapon;
// 			animationCycleTimer = 0;
// 			return;
// 		}
// 		if (weapon.isMelee and animationCycleTimer > weapon.projectileLifetime) //restores state after melee swing
// 		{
// 			animationCycleTimer = 0;
// 			isUsingWeapon = false;
// 			return;
// 		}

// 		isSetIdle = false;

// 		//doubles animation speed
// 		int x = int(animationCycleTimer * animationStates * 2) % animationStates; 

// 		sprite.setTextureRect(IntRect(Vector2i(weapon.actionSpriteSize.x * x, 4 * body.getSize().y), weapon.actionSpriteSize));
// 		sprite.setPosition(body.getPosition() - Vector2f(weapon.actionSpriteOffset));
// 	}

// 	else if (isMoving)
// 	{
// 		if (!latestAnimationUpdate) //skips 1 frame of lAU == 0
// 		{
// 			latestAnimationUpdate = elapsedTime;
// 			return;
// 		}
// 		if (latestAnimationType != animationStates::moving) //skips 1 frame of wrong animation type
// 		{
// 			latestAnimationType = animationStates::moving;
// 			animationCycleTimer = 0;
// 			return;
// 		}

// 		isSetIdle = false;

// 		//resets animation when direction is changed 
// 		//except on Y change while having constant X
// 		if (previousFrameDirection != currentDirection)
// 		{
// 			if (!(previousFrameDirection.x == currentDirection.x and currentDirection.x != 0 and
// 				previousFrameDirection.y != currentDirection.y))
// 				animationCycleTimer = 0;
// 		}

// 		int x = 1 + int(animationCycleTimer * animationStates) % animationStates;
// 		int y = 0;

// 		//prefers X over Y
// 		if (currentDirection.x == 1)		y = RIGHT;
// 		else if (currentDirection.x == -1)	y = LEFT;
// 		else if (currentDirection.y == 1)	y = DOWN;
// 		else if (currentDirection.y == -1)	y = UP;


// 		sprite.setTextureRect(IntRect(Vector2i(body.getSize().x * x, body.getSize().y * y), Vector2i(body.getSize())));
// 		sprite.setPosition(body.getPosition());
// 		previousFrameDirection = currentDirection;
// 	}

// 	else if(!isSetIdle)	//skips animation update when nothing of the above is present <----> should not be here for long
// 	{
// 		latestAnimationType = animationStates::idle;
// 		animationCycleTimer = latestAnimationUpdate = 0;
// 		previousFrameDirection = Vector2f(0, 0);

// 		if (currentSight.y == 1)
// 			sprite.setTextureRect(IntRect(Vector2i(0, DOWN * body.getSize().y), Vector2i(body.getSize())));
// 		else if (currentSight.y == -1)
// 			sprite.setTextureRect(IntRect(Vector2i(0, UP * body.getSize().y), Vector2i(body.getSize())));
// 		else if (currentSight.x == -1)
// 			sprite.setTextureRect(IntRect(Vector2i(0, LEFT * body.getSize().y), Vector2i(body.getSize())));
// 		else if (currentSight.x == 1)
// 			sprite.setTextureRect(IntRect(Vector2i(0, RIGHT * body.getSize().y), Vector2i(body.getSize())));

// 		sprite.setPosition(body.getPosition());
// 		isSetIdle = true;

// 		return;
// 	}

// 	animationCycleTimer += elapsedTime - latestAnimationUpdate;
// 	latestAnimationUpdate = elapsedTime;
// }

// bool Player::collisionCheck(const FloatRect& obstacle, bool allowCollision)
// {
// 	int x{0};
// 	x += Keyboard::isKeyPressed(Keyboard::D) ? 1 : 0;
// 	x += Keyboard::isKeyPressed(Keyboard::A) ? -1 : 0;

// 	int y{0};
// 	y += Keyboard::isKeyPressed(Keyboard::W) ? 1 : 0;
// 	y += Keyboard::isKeyPressed(Keyboard::S) ? -1 : 0;

// 	//if some direction key is pressed, change player direction
// 	//otherwise it stays the same
// 	if (x or y) 
// 		currentDirection = {x,y};
//}



// bool Player::collisionCheck(const FloatRect& obstacle)
// {
// 	if (obstacle.body.getGlobalBounds().intersects(body.getGlobalBounds()))
// 	{
// 		if (obstacle.allowCollision)
// 			return true;
// 		if (pendingDirection.x and pendingDirection.y)
// 			needOverride = true;

// 		if (!(currentDirection.x and currentDirection.y))
// 		{
// 			body.move(-currentDirection * latestDistanceCovered);
// 			return true;
// 		}

// 		const Vector2f UP = Vector2f(0, 1);
// 		const Vector2f RIGHT = Vector2f(1, 0);
// 		const Vector2f DOWN = -UP;
// 		const Vector2f LEFT = -RIGHT;

// 		if (currentDirection == UP + RIGHT)
// 		{
// 			body.move(latestDistanceCovered * LEFT);
// 			if (obstacle.body.getGlobalBounds().intersects(body.getGlobalBounds()))
// 			{
// 				body.move(latestDistanceCovered * (RIGHT + DOWN));
// 				overrideInputY = true; //upPressed = false;
// 			}
// 			else
// 				overrideInputX = true; //rightPressed = false;
// 		}

// 		else if (currentDirection == UP + LEFT)
// 		{
// 			body.move(latestDistanceCovered * RIGHT);
// 			if (obstacle.body.getGlobalBounds().intersects(body.getGlobalBounds()))
// 			{
// 				body.move(latestDistanceCovered * (LEFT + DOWN));
// 				overrideInputY = true; //upPressed = false;
// 			}
// 			else
// 				overrideInputX = true; //leftPressed = false;
// 		}

// 		else if (currentDirection == DOWN + RIGHT)
// 		{
// 			body.move(latestDistanceCovered * LEFT);
// 			if (obstacle.body.getGlobalBounds().intersects(body.getGlobalBounds()))
// 			{
// 				body.move(latestDistanceCovered * (RIGHT + UP));
// 				overrideInputY = true; //downPressed = false;
// 			}
// 			else
// 				overrideInputX = true; //rightPressed = false;
// 		}

// 		else if (currentDirection == DOWN + LEFT)
// 		{
// 			body.move(latestDistanceCovered * RIGHT);
// 			if (obstacle.body.getGlobalBounds().intersects(body.getGlobalBounds()))
// 			{
// 				body.move(latestDistanceCovered * (LEFT + UP));
// 				overrideInputY = true; //downPressed = false;
// 			}
// 			else
// 				overrideInputX = true; //leftPressed = false;
// 		}
// 		return true;
// 	}

// 	//Check if input override should still be present after current collision
// 	//
// 	//This checks pendingDirection (player input) to be clear from collision
// 	//If it's not, override is set back to true
// 	else if ((overrideInputX or overrideInputY) and currentDirection != Vector2f(0,0))
// 	{
// 		Vector2f pendingCheck((pendingDirection - currentDirection) * latestDistanceCovered);
// 		body.move(pendingCheck);
// 		if (obstacle.body.getGlobalBounds().intersects(body.getGlobalBounds()))
// 			needOverride = true; //caused nullptr twice (when was a pointer)
// 		body.move(-pendingCheck);
// 	}

// 	return false;
// }


// bool Player::interactionCheck(const gameObjectStationary& object)
// {
// 	const Vector2f interactionRadius = Vector2f(object.interactionRadius, object.interactionRadius);
	
// 	FloatRect interactionZone(object.body.getPosition() - interactionRadius, object.body.getSize() + 2.f * interactionRadius);
	
// 	return gameObject::collisionCheck(interactionZone);
// }


// void Player::collisionCheckInner(const FloatRect& area)
// {
// 	bool TL = area.contains(body.getPosition());
// 	bool TR = area.contains(body.getPosition() + Vector2f(body.getGlobalBounds().width, 0));
// 	bool BL = area.contains(body.getPosition() + Vector2f(0, body.getGlobalBounds().height));
// 	bool BR = area.contains(body.getPosition() + Vector2f(body.getGlobalBounds().width, body.getGlobalBounds().height));
// 	Vector2f solution(0, 0);
	
// 	if (!(TL and TR and BR and BL))
// 	{
// 		if (TL)
// 		{
// 			if (BL)
// 				solution = Vector2f(-1, 0);
// 			else if (TR)
// 				solution = Vector2f(0, -1);
// 			else
// 				solution = Vector2f(-1, -1);
// 		}

// 		else if (BR)
// 		{
// 			if (TR)
// 				solution = Vector2f(1, 0);
// 			else if (BL)
// 				solution = Vector2f(0, 1);
// 			else
// 				solution = Vector2f(1, 1);
// 		}

// 		else if (BL)
// 			solution = Vector2f(-1, 1);
// 		else if (TR)
// 			solution = Vector2f(1, -1);

// 		body.move(latestDistanceCovered * solution);
// 	}

// }

