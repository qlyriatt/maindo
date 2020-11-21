#pragma once
#include <SFML/Graphics.hpp>
#include "gameObject.h"

using namespace sf;

struct Projectile
{
	gameObject projectile;
	float range;
	Vector2f shotPosition, shotDirection, currentPosition;
};

class Weapon
{
public:
	Weapon();

	Projectile action(Vector2f sightDirection, Vector2f shotPosition);
	float range, damage, type, fireRate, projectileSpeed;
	Vector2f projectilePosition, shotPosition;
	bool has_fired;

private:
};

