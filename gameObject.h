﻿#pragma once
#include "gameObjectStationary.h"


class gameObject : public gameObjectStationary
{
public:
	
	gameObject();
	
	virtual ~gameObject();

	gameObject(Vector2f position, Vector2f size, Texture* texture = NULL, float speed = 0, bool allowCollision = 0, 
		Color bodyColor = Color::Black, Color outlineColor = Color::Red, float outlineThickness = 4); 

	bool collisionCheck(FloatRect obstacle);

	virtual bool collisionCheck(gameObject obstacle);

	virtual void collisionCheckInner(FloatRect area); //somewhat excessive (though probably not...)

	virtual void updatePosition(float elapsedTime);
	

	bool destroyable;

	// movement
	bool isMoving;
	float baseSpeed, speed;

	Vector2f currentSight, currentDirection;

	float latestUpdate, latestDistanceCovered;
};
