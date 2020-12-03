#pragma once
#include "gameObject.h"
#include "Weapon.h"

class Player : public gameObject
{
public:

	Player();

	Player(Vector2f position, Vector2f size, Texture* texture, float speed);

	void updatePosition(float elapsedTime);

	void updateMoveAnimation(float elapsedTime, const Texture* texture);

	bool collisionCheck(gameObject obstacle, bool* needOverride);

	bool interactionCheck(gameObject object);

	void collisionCheckInner(FloatRect area);

	Vector2f pendingDirection;
	bool overrideInputX;
	bool overrideInputY;

	Vector2f previousFrameDirection;
	float latestAnimationUpdate;
	bool isSetIdle;

	Weapon weapon;
	bool upPressed;
	bool rightPressed;
	bool downPressed;
	bool leftPressed;
	bool leftShiftPressed;
};


