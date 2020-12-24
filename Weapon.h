#pragma once
#include "gameObject.h"
using std::vector;


class proj : public gameObject
{
protected:
	proj() {};
public:

	virtual Vector2f swingHandle(const Clock& clock) { printf("handled in proj"); return Vector2f{ 0,0 }; };
	bool isMelee = { false };
	int penetration = { 0 };
};

class meleeHitbox : public proj
{
public:
	meleeHitbox() { isMelee = true; };

	float creationTime = { 0 };
	float lifeTime = { 0 };
	const vector<Vector2f>* hitboxPositions = nullptr;
	

	Vector2f swingHandle(const Clock& clock)
	{
		//int count = (clock.getElapsedTime().asSeconds() - creationTime) / lifeTime * hitboxPositions->size();
		printf("handled in melee");
		return Vector2f{ 1,1 };
	}
};

class rangedProjectile : public proj
{
	float traveledDistance = { 0 };
};



class Projectile : public gameObject
{	
protected:
	Projectile() {};
public:

	//MELEE
	Projectile(const int penetration, const float creationTime, const float lifeTime, const vector<Vector2f>& hitboxPositions)
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
	
	bool isMelee = { false };
	int	penetration = { 0 };

	//melee
	float creationTime = { 0 };
	float lifeTime = { 0 };
	const vector<Vector2f>* hitboxPositions = { nullptr };

	//ranged
	float traveledDistance = { 0 };
	float range = { 0 };
	Vector2f offsetShotPosition;
};


class Weapon
{
public:
	
	Weapon() {};

	//MELEE
	Weapon(const int ID, const float damage, const int penetration, const float swingDelay, const float swingTime,
		const vector<Vector2f>& hitboxPositions, const Vector2f& hitboxSize);

	//RANGED
	Weapon(const int ID, const float damage, const int penetration, const float shotDelay, const float range, const float projectileSpeed,
		const int ammoCapacity, const float reloadTime, const Texture& projectileTexture);

	//push projectile from the weapon into one shared vector
	void action(vector<Projectile>& projectiles, const gameObject& projectileSource, const Clock& clock);

	//look for reload options and handle them
	void reloadHandle(const Clock& clock);


	//any
	bool		isMelee = { false };
	int			penetration = { 0 };
	int			ID = { 0 };
	float		latestShotTime = { 0 };
	float		damage = { 0 };
	float		shotDelay = { 0 };

	//melee?
	float				projectileLifetime = { 0 };
	Vector2i			actionSpriteOffset;
	Vector2i			actionSpriteSize;
	Vector2f			hitboxSize;
	vector<Vector2f>	hitboxPositions;

	//ranged
	int		ammoCapacity = { 0 };
	int		currentAmmo = { 0 };
	float	range = { 0 };
	float	projectileSpeed = { 0 };
	float	reloadTimer = { 0 };
	float	latestReloadUpdate = { 0 };
	float	reloadTime = { 0 };
	const Texture* projectileTexture = { nullptr };
};

