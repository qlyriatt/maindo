#pragma once
#include "gameObject.h"
#include "Weapon.h"

class Player : public gameObject
{
public:

	Player();

	Player(Vector2f position, Vector2f size, Texture* texture, float speed);

	void updatePosition(float elapsedTime);

	
	Weapon weapon;
	bool upPressed;
	bool rightPressed;
	bool downPressed;
	bool leftPressed;
	bool leftShiftPressed;
};


