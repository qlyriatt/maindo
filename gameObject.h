#pragma once
#include "gameObjectStationary.h"


class gameObject : public gameObjectStationary
{
protected:
	gameObject() {};
public:

	//simple initializer with one texture state
	gameObject(const Vector2f& position, const Texture& texture);

	//initializer for testing
	gameObject(const Vector2f& position, const Vector2f& size, const float basespeed = 0, 
		const int interactionType = 0, const int interactionTypeSpeciality = 0, const bool allowCollision = false);

	//final constructor
	gameObject(const Vector2f& position, const Texture& texture, const size_t animationStates, const float basespeed, const bool allowCollision,
		const bool isDestroyable, const int interactionType, const int interactionTypeSpeciality, const size_t interactionRadius = 10);

	
	bool collisionCheck(const FloatRect& obstacle) const;

	//does not move objects
	bool collisionCheck(const gameObject& obstacle) const;

	virtual bool collisionCheck(const gameObject& obstacle);

	virtual void collisionCheckInner(const FloatRect& area); //somewhat excessive (though probably not...)

	virtual void updatePosition(const Clock& clock);


	//movement
	bool		isMoving = { false };
	int			ID = { 0 };
	float		basespeed = { 0 };
	float		speed = { 0 };
	float		latestMoveUpdate = { 0 };
	float		latestDistanceCovered = { 0 };
	Vector2f	currentSight = { 1,0 };
	Vector2f	currentDirection;
};
