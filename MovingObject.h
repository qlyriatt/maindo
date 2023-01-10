#pragma once
#include "BasicObject.h"
using sf::Vector2i, sf::Vector2f;

/*
	Vector2 { X, Y };

		    Y

		   -1
			|		  
		    |
		    |
	-1______0______>1  X
		    |
		    |
		    |
		    1
*/
class MovingObject : public BasicObject
{
protected:

	bool		isMoving = false;
	float		baseSpeed = 0;
	float		currentSpeed = 0;
	float		latestMoveUpdateTime = 0;
	float		latestDistanceCovered = 0;
	Vector2f	currentSight {1, 0};
	Vector2f	currentDirection {0, 0}; 
	Vector2f 	pendingPositionVector {0, 0};

private:
	// create a pending movement for collision checking.
	// does not change current position of an object
	void createPendingPositionVector(float elapsedTime); 

public:
	bool collisionCheck(const RectangleShape& obstacle, bool allowCollision);

	void updateState() override {};

	virtual void updatePosition(float elapsedTime);
};
