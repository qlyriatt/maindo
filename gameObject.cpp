#include "gameObject.h"

gameObject::gameObject() : gameObjectStationary()
{
	isMoving = false;
	baseSpeed = speed = latestUpdate = latestDistanceCovered = 0;
}

gameObject::gameObject(Vector2f position, Vector2f size, Texture* texture, float speed,
	bool allowCollision, Color bodyColor, Color outlineColor, float outlineThickness) : gameObjectStationary(position, size, texture, allowCollision, bodyColor, outlineColor, outlineThickness)
{	
	this->speed = this->baseSpeed = speed;

	currentSight = Vector2f(1, 0); //RIGHT

	isMoving = false;

	isDestroyable = true;

	latestUpdate = latestDistanceCovered = 0;

	clockOffset = 0;
}

bool gameObject::collisionCheck(FloatRect obstacle)
{
	if (obstacle.intersects(body.getGlobalBounds()))
		return true;
	return false;
}

bool gameObject::collisionCheck(gameObject obstacle)
{
	if (obstacle.body.getGlobalBounds().intersects(body.getGlobalBounds()))
	{
		if (!obstacle.allowCollision)
			body.move(-currentDirection * latestDistanceCovered);		
		return true;
	}
	return false;
}

void gameObject::collisionCheckInner(FloatRect area)
{
	bool TL = area.contains(body.getPosition());
	bool TR = area.contains(body.getPosition() + Vector2f(body.getGlobalBounds().width, 0));
	bool BL = area.contains(body.getPosition() + Vector2f(0, body.getGlobalBounds().height));
	bool BR = area.contains(body.getPosition() + Vector2f(body.getGlobalBounds().width,body.getGlobalBounds().height));

	if (!(TL and TR and BR and BL))
		body.move(-currentDirection * latestDistanceCovered);
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
	if (!(isMoving and speed))
	{
		latestUpdate = 0;
		//animationCycleTimer = 0;			//eta suka ubila mne 2 chasa blyatttttt
		return;
	}

	if (!latestUpdate)	//skips one still frame after beginning of motion, not essential
	{
		latestUpdate = elapsedTime;
		return;
	}
	
	latestDistanceCovered = (elapsedTime - latestUpdate) * speed;
	latestUpdate = elapsedTime;
	body.move(currentDirection * latestDistanceCovered);
}

