#pragma once
#include "gameObject.h"
#include "Weapon.h"

class Player : public gameObject
{
public:

	Player();

	Player(float speed, Vector2f position, Texture* texture);

	// a lot of stuff should be transfered to gameobject instead

	Clock clock;

	Weapon weapon;
	Vector2f sight;

	bool upPressed;
	bool rightPressed;
	bool downPressed;
	bool leftPressed;
	bool leftShiftPressed;

	bool moving;

	Vector2f getSight();

	Vector2f getDirection();

	void update();

	void blink();
};


