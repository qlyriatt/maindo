#include "gameObject.h"
#include <iostream>

gameObject::gameObject()
{
	moving = false;
	baseSpeed = speed = 0;
	currentDirection = Vector2f(0, 0);
	latestUpdate = 0;
	latestDistanceCovered = 0;
}

gameObject::~gameObject()
{

}

//should be removed later
gameObject::gameObject(float speed, Vector2f bodyPosition, Vector2f bodySize, bool allowCollision, Color bodyColor, Color outlineColor,
	float outlineThickness, short int interactionType, short int interactionRadius)
{
	//initial values
	
	this->speed = this->baseSpeed = speed;
	body.setPosition(bodyPosition);
	body.setSize(bodySize);
	this->allowCollision = allowCollision;
	body.setFillColor(bodyColor);
	body.setOutlineColor(outlineColor);
	body.setOutlineThickness(outlineThickness);
	this->interactionType = interactionType;
	this->interactionRadius = interactionRadius;

	// movement

	moving = false;
	latestUpdate = 0;
	latestDistanceCovered = 0;
}

gameObject::gameObject(float speed, Vector2f spritePosition, Texture* texture, bool allowCollision, int interactionType, int interactionRadius)
{
	//initial values
	
	this->speed = this->baseSpeed = speed;
	sprite.setPosition(spritePosition);
	sprite.setTexture(*texture);
	this->allowCollision = allowCollision;
	this->interactionType = interactionType;
	this->interactionRadius = interactionRadius;

	// compatibility

	body.setPosition(spritePosition);
	body.setSize(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
	body.setFillColor(Color::Transparent);

	// movement
	moving = false;
	latestUpdate = 0;
	latestDistanceCovered = 0;
}


//better FIX something else

bool gameObject::collisionCheck(gameObject obstacle)
{
	if (obstacle.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()))
	{
		if (obstacle.allowCollision)
			return true;

		Vector2f solution = -currentDirection * latestDistanceCovered;
		sprite.move(solution);
		body.move(solution);

		return true;
	}
	return false;
}

bool gameObject::collisionCheck(gameObject obstacle, int)
{
	if (obstacle.body.getGlobalBounds().intersects(body.getGlobalBounds()))
	{
		if (obstacle.allowCollision)
			return true;

		Vector2f solution = -currentDirection * latestDistanceCovered;
		sprite.move(solution);
		body.move(solution);

		return true;
	}
	
	return false;
}

void gameObject::collisionCheckInner(FloatRect area)
{
	bool TL = area.contains(sprite.getPosition());
	bool TR = area.contains(sprite.getPosition() + Vector2f(sprite.getGlobalBounds().width,0));
	bool BL = area.contains(sprite.getPosition() + Vector2f(0,sprite.getGlobalBounds().height));
	bool BR = area.contains(sprite.getPosition() + Vector2f(sprite.getGlobalBounds().width,sprite.getGlobalBounds().height));

	if (!(TL and TR and BR and BL))
	{
		Vector2f solution = -currentDirection * latestDistanceCovered;
		sprite.move(solution);
		body.move(solution);
	}
}

//void gameObject::collisionCheckInner(FloatRect area)
//{
//	bool TL = area.contains(sprite.getPosition());
//	bool TR = area.contains(sprite.getPosition() + Vector2f(sprite.getGlobalBounds().width,0));
//	bool BL = area.contains(sprite.getPosition() + Vector2f(0,sprite.getGlobalBounds().height));
//	bool BR = area.contains(sprite.getPosition() + Vector2f(sprite.getGlobalBounds().width,sprite.getGlobalBounds().height));
//
//	if (!(TL and TR and BR and BL))
//	{
//		if (TL)
//		{
//			if (BL)
//				sprite.move(-speed, 0);
//			else if (TR)
//				sprite.move(0, -speed);
//			else
//				sprite.move(-speed, -speed);
//		}
//
//		else if (BR)
//		{
//			if (TR)
//				sprite.move(speed, 0);
//			else if (BL)
//				sprite.move(0, speed);
//			else
//				sprite.move(speed, speed);
//		}
//
//		else if (BL)
//			sprite.move(-speed, speed);
//		else if (TR)
//			sprite.move(speed, -speed);
//	}
//}

void gameObject::updatePosition(float elapsedTime)
{
	if (!(moving and speed))
	{
		latestUpdate = 0;
		return;
	}

	if (!latestUpdate)
	{
		latestUpdate = elapsedTime;
		return;
	}

	latestDistanceCovered = (elapsedTime - latestUpdate) * speed;
	Vector2f distance = currentDirection * latestDistanceCovered;

	latestUpdate = elapsedTime;
	body.move(distance);
	sprite.move(distance);
}
