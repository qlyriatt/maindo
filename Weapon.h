#pragma once
#include "gameObject.h"
using std::vector;


struct Projectile : public gameObject
{
	bool		isMelee;
	int			penetration;
	float		range;
	float		creationTime;
	float		lifeTime;
	Vector2f	currentPosition;
	void*		gameObjectSource;
	void*		weaponSource;
};

class Weapon
{
public:

	Weapon();
	
	Weapon(int ID, float range, float projectileSpeed, float ammoCapacity, const Texture* projectileTexture = NULL, 
		float fireRate = 1, float reloadTime = 1, float damage = 0);

	void action(void* projectileSource, Vector2f shotDirection, Vector2f shotPosition, float elapsedTime, vector<Projectile>& projectiles);

	//any
	bool		isMelee;
	int			ammoCapacity;
	int			currentAmmo;
	int			projectilePenetration;
	int			ID;
	float		latestShotTime;
	float		projectileLifetime;
	float		damage;
	float		fireRate;
	Vector2i			actionSpriteOffset;
	Vector2i			actionSpriteSize;
	Vector2f			hitboxSize;
	vector<Vector2f>	hitboxPositions;
	const Texture*		projectileTexture;


	//ranged
	float	range;
	float	projectileSpeed;
	float	reloadTimer;	
	float	latestReloadUpdate;
	float	reloadTime;
};

