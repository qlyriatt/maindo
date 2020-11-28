#pragma once
#include "gameObjectStationary.h"


class gameObject : public gameObjectStationary
{
public:
	
	gameObject();
	
	virtual ~gameObject();

	gameObject(Vector2f position, Vector2f size, Texture* texture = NULL, float speed = 0, bool allowCollision = 0, 
		Color bodyColor = Color::Black, Color outlineColor = Color::Red, float outlineThickness = 4); 

	bool collisionCheck(gameObject);

	void collisionCheckInner(FloatRect); //somewhat excessive (though probably not...)

	virtual void updatePosition(float elapsedTime);
	
	void script(Vector2f node, Vector2f playerPosition, float elapsedTime);

	int movingSwitch = 0;
	float movingSwitchTime = 0;
	float latestmove = 0;
	float movedToNode = 0;
	
	// movement
	bool isMoving;
	float baseSpeed, speed;

	Vector2f currentSight, currentDirection;

	float latestUpdate, latestDistanceCovered;
};
