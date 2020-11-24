#pragma once
#include "gameObjectStationary.h"


class gameObject : public gameObjectStationary
{
public:
	
	gameObject();
	
	virtual ~gameObject();

	gameObject(float speed, Vector2f bodyPosition, Vector2f bodySize, bool allowCollision = 0, Color bodyColor = Color::Black, Color outlineColor = Color::Red, float outlineThickness = 4,
		 short int interactionType = 0, short int interactionRadius = 5); //easier, without a sprite //should be removed later
	
	gameObject(float speed, Vector2f spritePosition, Texture* texture, bool allowCollision = 0, int interactionType = 0, int interactionRadius = 0);

	bool collisionCheck(gameObject); //works with sprites

	bool collisionCheck(gameObject, int); 

	void collisionCheckInner(FloatRect); //somewhat excessive (though probably not...)

	virtual void updatePosition(float elapsedTime);
	
	void script(int type, Vector2f node, Vector2f playerPosition, float elapsedTime);

	bool moving;

	int movingSwitch = 0;
	float movingSwitchTime = 0;
	float latestmove = 0;
	int movedToNode = 0;
	
	float baseSpeed;  
	float speed; 
	
	Vector2f currentSight;
	Vector2f currentDirection;
	//Clock objectClock;
	float latestUpdate;
	float latestDistanceCovered;
};
