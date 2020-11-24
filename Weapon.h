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

	Weapon(float range, float projectileSpeed, Color projectileColor = Color::White, float fireRate = 0, float damage = 0, int weaponType = 0,
		Texture* weaponTexture = NULL, Texture* projectileTexture = NULL);

	Projectile action(Vector2f shotDirection, Vector2f shotPosition);

	
	Sprite sprite;

	Texture* projectileTexture;

	float range, damage, fireRate, projectileSpeed, type;

	//compatibility
	RectangleShape body;
	Color projectileColor;
};

