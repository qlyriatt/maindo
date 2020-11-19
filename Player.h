#pragma once
#include "Entity.h"


class Player : public gameObject
{
public:

	Player();
	Player(float, bool, short int, Vector2f, Vector2f, Color, float);

	Player(float speed, Vector2f position, Texture* texture);
	Clock clock;

	bool upPressed;
	bool rightPressed;
	bool downPressed;
	bool leftPressed;
	bool leftShiftPressed;

	bool moving;

	Vector2f getdirection();
	void update();
	void update(int);

	void blink();

};


