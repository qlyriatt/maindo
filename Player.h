#pragma once
#include "gameObject.h"
#include "Weapon.h"

class Player : public gameObject
{
public:

	Player();

	Player(float speed, Vector2f position, Texture* texture);

	// a lot of stuff ---WAS--- transfered to gameobject instead

	void updatePosition(float elapsedTime);

	Weapon weapon;

	bool upPressed;
	bool rightPressed;
	bool downPressed;
	bool leftPressed;
	bool leftShiftPressed;
};


