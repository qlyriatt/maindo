#pragma once
#include "gameObjectStationary.h"


class gameObject : public gameObjectStationary
{	
public:

	gameObject();
	
	gameObject(Vector2f position, Vector2f size, const Texture* texture = NULL, float speed = 0, bool allowCollision = 0, 
		Color bodyColor = Color::Black, Color outlineColor = Color::Red, float outlineThickness = 4); 
	
	bool collisionCheck(const FloatRect& obstacle) const;

	//does not move objects
	bool collisionCheck(const gameObject& obstacle) const;

	virtual bool collisionCheck(const gameObject& obstacle);

	virtual void collisionCheckInner(const FloatRect& area); //somewhat excessive (though probably not...)

	virtual void updatePosition(float elapsedTime);
	
	
	int			ID;
	bool		isMoving;
	float		basespeed;
	float		speed;
	float		latestUpdate;
	float		latestDistanceCovered;
	Vector2f	currentSight;
	Vector2f	currentDirection;
};
