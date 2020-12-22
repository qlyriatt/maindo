#include "gameObject.h"

gameObject::gameObject() : gameObjectStationary()
{
	isMoving = false;
	basespeed = speed = latestUpdate = latestDistanceCovered = 0;
	ID = 0;
}

gameObject::gameObject(Vector2f position, Vector2f size, const Texture* texture, float speed,
	bool allowCollision, Color bodyColor, Color outlineColor, float outlineThickness) : gameObjectStationary(position, size, texture, allowCollision, bodyColor, outlineColor, outlineThickness)
{	
	this->speed = this->basespeed = speed;

	currentSight = Vector2f(1, 0); //RIGHT

	isMoving = false;

	isDestroyable = true;

	latestUpdate = latestDistanceCovered = 0;

	ID = 0;
}

bool gameObject::collisionCheck(const FloatRect& obstacle) const
{
	if (body.getGlobalBounds().intersects(obstacle))
		return true;
	return false;
}

bool gameObject::collisionCheck(const gameObject& obstacle) const
{
	if (body.getGlobalBounds().intersects(obstacle.body.getGlobalBounds()))
		return true;
	return false;
}

bool gameObject::collisionCheck(const gameObject& obstacle)
{
	if (obstacle.body.getGlobalBounds().intersects(body.getGlobalBounds()))
	{
		if (!obstacle.allowCollision)
			body.move(-currentDirection * latestDistanceCovered);		
		return true;
	}
	return false;
}

void gameObject::collisionCheckInner(const FloatRect& area)
{
	bool TL = area.contains(body.getPosition());
	bool TR = area.contains(body.getPosition() + Vector2f(body.getGlobalBounds().width, 0));
	bool BL = area.contains(body.getPosition() + Vector2f(0, body.getGlobalBounds().height));
	bool BR = area.contains(body.getPosition() + Vector2f(body.getGlobalBounds().width,body.getGlobalBounds().height));

	if (!(TL and TR and BR and BL))
		body.move(-currentDirection * latestDistanceCovered);
}

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

