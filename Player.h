#pragma once
#include "gameObject.h"
#include "Weapon.h"
using std::vector;

class Player : public gameObject
{
public:

	Player();

	Player(Vector2f position, Vector2f size, const Texture* texture, float speed);

	void updatePosition(float elapsedTime);

	void updateAnimation(float elapsedTime, const Texture* texture);

	bool collisionCheck(const gameObject& obstacle, bool* needOverride);

	bool interactionCheck(const gameObject& object);

	void collisionCheckInner(const FloatRect& area);

	enum animationStates //should be moved to gO or smwh else
	{
		idle = 0,
		moving,
		usingWeapon
	};

	//movement advanced
	Vector2f	pendingDirection;
	bool		overrideInputX;
	bool		overrideInputY;

	//animation
	bool		isSetIdle;
	bool		isUsingWeapon;
	int			latestAnimationType;
	float		latestAnimationUpdate;
	Vector2f	previousFrameDirection;
	Sprite		sprite;

	//inventory
	bool		isInventoryOpen;
	int			health;
	int			maxHealth;
	vector<int> inventorySlots;

	//basic
	Weapon		weapon;
	bool		upPressed;
	bool		rightPressed;
	bool		downPressed;
	bool		leftPressed;
	bool		leftShiftPressed;
};


