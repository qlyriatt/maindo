#pragma once
#include "Entity.h"


class Player : public Entity
{
public:

	Player();
	Player(float,float,float,float,float);
	
	bool upPressed;
	bool rightPressed;
	bool downPressed;
	bool leftPressed;
	
	void update();
	void update(int);
	Vector2f getcenter();

private:
};


