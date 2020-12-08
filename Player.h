#pragma once
#include "gameObject.h"
#include "Weapon.h"

class Player : public gameObject
{
public:

	Player();

	Player(Vector2f position, Vector2f size, Texture* texture, float speed);

	void updatePosition(float elapsedTime);

	void updateAnimation(float elapsedTime, const Texture* texture);

	bool collisionCheck(gameObject obstacle, bool* needOverride);

	bool interactionCheck(gameObject object);

	void collisionCheckInner(FloatRect area);

	Vector2f pendingDirection;
	bool overrideInputX;
	bool overrideInputY;

	Sprite sprite;
	Vector2f previousFrameDirection;
	float latestAnimationUpdate;
	bool isSetIdle;
	bool isUsingWeapon;
	int latestAnimationType;
	float animationTimerOffset;

	bool isInventoryOpen;
	std::vector<int> inventorySlots;

	Weapon weapon;
	bool upPressed;
	bool rightPressed;
	bool downPressed;
	bool leftPressed;
	bool leftShiftPressed;
};


