#pragma once
#include "gameObject.h"
#include "Weapon.h"

class Player : public gameObject
{
public:

	Player();

	Player(Vector2f position, Vector2f size, Texture* texture, float speed);

	void updatePosition(float elapsedTime);

	bool checkPending(gameObject obstacle);

	bool collisionCheck(gameObject obstacle, bool* needOverride);

	bool interactionCheck(gameObject object);

	void collisionCheckInner(FloatRect area);

	Vector2f pendingDirection;
	Vector2f overrideVector;
	Weapon weapon;
	bool upPressed;
	bool rightPressed;
	bool downPressed;
	bool leftPressed;
	bool leftShiftPressed;
};


