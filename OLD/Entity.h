#pragma once
#include "Weapon.h"

//useless but essential
//either might be wrong
class Entity : public gameObject
{
protected:
	Entity() {};
public:

	Entity(const int type, const Vector2f& position, const Vector2f& size, const float speed = 0);

	void script(Vector2f node, Vector2f playerPosition, const float elapsedTime, vector<Projectile>& projectiles);

	Weapon weapon;
	int type = { 0 };
	int movingSwitch = { 0 };
	float movingSwitchTime = { 0 };
	float latestmove = { 0 };
	float movedToNode = { 0 };
};

