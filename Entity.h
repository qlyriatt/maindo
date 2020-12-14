#pragma once
#include "Weapon.h"

//useless but essential
//either might be wrong
class Entity : public gameObject
{
public:
	Entity();

	Entity(int type, Vector2f position, Vector2f size, const Texture* texture = NULL, float speed = 0, bool allowCollision = 0,
		Color bodyColor = Color::Black, Color outlineColor = Color::Red, float outlineThickness = 4);

	void script(Vector2f node, Vector2f playerPosition, float elapsedTime, vector<Projectile>& projectiles);

	Weapon weapon;
	int type;
	int movingSwitch = 0;
	float movingSwitchTime = 0;
	float latestmove = 0;
	float movedToNode = 0;
};

