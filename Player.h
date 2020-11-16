#pragma once
#include "Entity.h"


class Player : public Entity
{
public:

	Player();
	Player(float,float,float,float,float);
	
	Clock clock;

	bool upPressed;
	bool rightPressed;
	bool downPressed;
	bool leftPressed;
	bool leftShiftPressed;

	bool moving;

	virtual Vector2f getdirection();
	void update();
	void update(int);

	void blink();


private:
};


