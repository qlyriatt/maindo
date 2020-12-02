#pragma once
#include <SFML/Graphics.hpp>
#include "gameObject.h"

using namespace sf;

struct Projectile : public gameObject
{
	float range;
	int penetration;
	Vector2f currentPosition;
};

class Weapon
{
public:

	Weapon();
	
	Weapon(float range, float projectileSpeed, Texture* weaponTexture = NULL, Texture* projectileTexture = NULL, float fireRate = 1, float damage = 0);

	void action(Vector2f shotDirection, Vector2f shotPosition, float elapsedTime, std::vector<Projectile>* projectiles);

	float latestShotTime;

	RectangleShape body;
	Texture* projectileTexture;
	float range, damage, fireRate, projectileSpeed, projectilePenetration;
};

