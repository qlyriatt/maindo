#pragma once
#include <SFML/Graphics.hpp>
#include "gameObject.h"

using namespace sf;

struct Projectile : public gameObject
{
	float range;
	Vector2f currentPosition;
};

class Weapon
{
public:

	Weapon();

	Weapon(float range, float projectileSpeed, Texture* weaponTexture = NULL, Texture* projectileTexture = NULL, float fireRate = 0, float damage = 0);

	Projectile action(Vector2f shotDirection, Vector2f shotPosition);


	RectangleShape body;
	Texture* projectileTexture;
	float range, damage, fireRate, projectileSpeed;
};

