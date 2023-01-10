#include "MovingObject.h"


void MovingObject::createPendingPositionVector(float elapsedTime)
{
	latestDistanceCovered = (elapsedTime - latestMoveUpdateTime) * currentSpeed;
	latestMoveUpdateTime = elapsedTime;
	pendingPositionVector = currentDirection * latestDistanceCovered;
}

bool MovingObject::collisionCheck(const RectangleShape& obstacle, bool allowCollision)
{
	//if object does not want to move, return simple collision check state
	if (pendingPositionVector == Vector2f{0,0})
	{
		return BasicObject::collisionCheck(obstacle);
	}

	Vector2f currentPosition = body.getPosition(); //current position
	 
	RectangleShape pendingBodyPosition;
	pendingBodyPosition.setPosition(currentPosition + pendingPositionVector); //position that the object wants to be in

	//check what the pending move leads to
	if (pendingBodyPosition.getGlobalBounds().intersects(obstacle.getGlobalBounds())) //collision exists
	{
		if (!allowCollision and !this->allowCollision) //both the obstacle and the current object disallow collision
		{
			//this configuration also checks for simultaneous collision at both X and Y (trying to move into the corner)

			pendingBodyPosition.setPosition(currentPosition.x, currentPosition.y + pendingPositionVector.y); //reset X, check again
			if (pendingBodyPosition.getGlobalBounds().intersects(obstacle.getGlobalBounds())) //collision happens at Y axis
				pendingPositionVector.y = 0; //prohibit movement on Y axis
			
			pendingBodyPosition.setPosition(currentPosition.x + pendingPositionVector.x, currentPosition.y); //reset Y, check
			if (pendingBodyPosition.getGlobalBounds().intersects(obstacle.getGlobalBounds())) //collision happens at X axis
				pendingPositionVector.x = 0; //prohibit movement on X axis
		}
		return true;
	}
	return false;
}

// takes direction vector and time, moves object
void MovingObject::updatePosition(float elapsedTime)
{
	if (!(isMoving and currentSpeed)) //skips creation if the object is static or standing still
	{
		latestMoveUpdateTime = 0;
		return;
	}

	if (!latestMoveUpdateTime)	//skips one still frame after beginning of motion, not essential
	{
		latestMoveUpdateTime = elapsedTime;
		return;
	}

	createPendingPositionVector(elapsedTime);
	body.move(pendingPositionVector);
}