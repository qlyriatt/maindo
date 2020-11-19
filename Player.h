#pragma once
#include "gameObject.h"
#include "Weapon.h"

class Player : public gameObject
{
public:

	Player();

	Player(float speed, Vector2f position, Texture* texture);
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
	Vector2f getdirection();
	void update();
	void update(int);

	void blink();

};


