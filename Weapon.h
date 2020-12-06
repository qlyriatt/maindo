#pragma once
#include "gameObject.h"

struct Projectile : public gameObject
{
	void* gameObjectSource;
	void* weaponSource;
	float creationTime;
	float lifeTime;
	bool isMelee;

	float range;
	int penetration;
	Vector2f currentPosition;
};

class Weapon
{
public:

	Weapon();
	
	Weapon(int ID, float range, float projectileSpeed, float ammoCapacity, Texture* projectileTexture = NULL, 
		float fireRate = 1, float reloadTime = 1, float damage = 0);

	void action(void* projectileSource, Vector2f shotDirection, Vector2f shotPosition, float elapsedTime, std::vector<Projectile>* projectiles);

	//any
	float latestShotTime;
	int ammoCapacity;
	int currentAmmo;
	float projectileLifetime;
	const Texture* projectileTexture;
	int projectilePenetration;
	bool isMelee;
	float damage;
	float fireRate;
	int ID;
	Vector2i actionSpriteOffset;
	Vector2i actionSpriteSize;
	Vector2f hitboxSize;
	std::vector<Vector2f> hitboxPositions;


	//ranged
	float range;
	float projectileSpeed;
	float reloadTimer;	
	float latestReloadUpdate;
	float reloadTime;
};

