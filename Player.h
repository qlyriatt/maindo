#pragma once
#include "Weapon.h"


class Player : public gameObject
{
public:

	Player(const Vector2f& position, const Vector2f& size, const Texture& texture, const size_t animationStates, const float speed);

	void updatePosition(const float elapsedTime) override;

	void updateAnimation(float elapsedTime, const Texture* texture);
	
	bool collisionCheck(const gameObjectStationary& obstacle, bool& needOverride);
	
	bool interactionCheck(const gameObjectStationary& object);

	void collisionCheckInner(const FloatRect& area);

	enum animationStates //should be moved to gO or smwh else
	{
		idle = 0,
		moving,
		usingWeapon
	};

	//movement advanced
	Vector2f	pendingDirection;
	bool		overrideInputX = { false };
	bool		overrideInputY = { false };

	//animation
	bool		isSetIdle = { true };
	bool		isUsingWeapon = { false };
	int			latestAnimationType = { 0 };
	float		latestAnimationUpdate = { 0 };
	Vector2f	previousFrameDirection;
	Sprite		sprite;

	//inventory
	bool		interactionFlag = { false };
	int			health = { 0 };
	int			maxHealth = { 0 };
	vector<int> inventorySlots;

	//basic
	Weapon		weapon;
	bool		upPressed = { false };
	bool		rightPressed = { false };
	bool		downPressed = { false };
	bool		leftPressed = { false };
	bool		leftShiftPressed = { false };
};


