#include "BasicObject.h" // includes Graphics.hpp, using namespace sf


/*
	Vector2 { X, Y };

		    Y

		    1		  
		    ^
		    |
		    |
	-1______0______>1  X
		    |
		    |
		    |
		   -1
*/
class MovingObject : public BasicObject
{
protected:

    MovingObject();
    virtual ~MovingObject();

	bool		isMoving = {false};
	float		baseSpeed = {0};
	float		currentSpeed = {0};
	float		latestMoveUpdate = {0};
	float		latestDistanceCovered = {0};
	Vector2f	currentSight = {1,0};
	Vector2f	currentDirection = {1,0}; 
	Vector2f 	pendingPositionVector = {0,0};

private:

	// create a pending movement for collision checking.
	// does not change current position of an object
	void createPendingPositionVector(float elapsedTime); 

public:

	bool collisionCheck(const RectangleShape& obstacle, bool allowCollision);

	void updateState() override;
};
