#pragma once
#include "gameObject.h"
using std::vector;


struct Projectile : public gameObject
{	
	//MELEE
	Projectile(int penetration, float creationTime, float lifeTime, const vector<Vector2f>& hitboxPositions)
	{	
		this->isMelee = true;
		this->allowCollision = true;

		this->penetration = penetration;
		this->creationTime = creationTime;
		this->lifeTime = lifeTime;
		this->hitboxPositions = &hitboxPositions;
	}

	//RANGED
	Projectile(int penetration, float range)
	{
		this->isMelee = false;
		this->isMoving = true;
		this->traveledDistance = 0;
		this->offsetShotPosition = { 0,0 };

		this->penetration = penetration;
		this->range = range;
	}

	//move hitboxes according to hitboxPositions
	//
	//melee only
	Vector2f swingHandle(const Clock& clock);
	
	bool isMelee;
	int	penetration;

	//melee
	float creationTime;
	float lifeTime;
	const vector<Vector2f>* hitboxPositions;

	//ranged
	float traveledDistance;
	float range;
	Vector2f offsetShotPosition;
};


class Weapon
{
public:

	Weapon();
	
	//MELEE
	Weapon(int ID, float damage, int penetration, float swingDelay, float swingTime,
		const vector<Vector2f>& hitboxPositions, const Vector2f& hitboxSize);

	//RANGED
	Weapon(int ID, float damage, int penetration, float shotDelay, float range, float projectileSpeed,
		int ammoCapacity, float reloadTime, const Texture& projectileTexture);

	//push projectile from the weapon into one shared vector
	void action(vector<Projectile>& projectiles, const gameObject& projectileSource, const Clock& clock);

	//look for reload options and handle them
	void reloadHandle(const Clock& clock);

	//any
	bool		isMelee;
	int			penetration;
	int			ID;
	float		latestShotTime;
	float		damage;
	float		shotDelay;


	//melee?
	float projectileLifetime;
	Vector2i			actionSpriteOffset;
	Vector2i			actionSpriteSize;
	Vector2f			hitboxSize;
	vector<Vector2f>	hitboxPositions;


	//ranged
	int		ammoCapacity;
	int		currentAmmo;
	float	range;
	float	projectileSpeed;
	float	reloadTimer;	
	float	latestReloadUpdate;
	float	reloadTime;
	const Texture* projectileTexture;
};

