#include "gameObject.h"


//minimal
gameObject::gameObject(const Vector2f& position, const Texture& texture) : gameObjectStationary(position, texture) {}

//testing
gameObject::gameObject(const Vector2f& position, const Vector2f& size, const float basespeed, 
	const int interactionType, const int interactionTypeSpeciality, const bool allowCollision) : 
	gameObjectStationary(position, size, interactionType, interactionTypeSpeciality, allowCollision)
{
	this->speed = this->basespeed = basespeed;
}

//final
gameObject::gameObject(const Vector2f& position, const Texture& texture, const size_t animationStates, const float basespeed, 
	const bool allowCollision, const bool isDestroyable, const int interactionType, const int interactionTypeSpeciality, const size_t interactionRadius) :
	gameObjectStationary(position, texture, animationStates, allowCollision, isDestroyable, interactionType, interactionTypeSpeciality, interactionRadius)
{
	this->speed = this->basespeed = basespeed;
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

void gameObject::updatePosition(const Clock& clock)
{
	float elapsedTime = clock.getElapsedTime().asSeconds();

	if (!(isMoving and speed)) //skips update if the object is static or standing still
	{
		latestMoveUpdate = 0;
		return;
	}

	if (!latestMoveUpdate)	//skips one still frame after beginning of motion, not essential
	{
		latestMoveUpdate = elapsedTime;
		return;
	}
	
	latestDistanceCovered = (elapsedTime - latestMoveUpdate) * speed;
	latestMoveUpdate = elapsedTime;
	body.move(currentDirection * latestDistanceCovered);
}

