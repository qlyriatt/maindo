#include "Weapon.h"


Vector2f Projectile::swingHandle(const Clock& clock)
{
	//__pragma (warning(suppress : 4244))
	int count = (clock.getElapsedTime().asSeconds() - creationTime) / lifeTime * hitboxPositions->size();
	return hitboxPositions->at(count);
}

//melee
Weapon::Weapon(const int ID, const float damage, const int penetration, const float swingDelay, const float swingTime,
	const vector<Vector2f>& hitboxPositions, const Vector2f& hitboxSize)
{
	this->isMelee = true;


	this->ID = ID;
	this->damage = damage;
	this->penetration = penetration;
	this->shotDelay = swingDelay;
	this->projectileLifetime = swingTime;
	this->hitboxPositions = hitboxPositions;
	this->hitboxSize = hitboxSize;
}

//ranged
Weapon::Weapon(const int ID, const float damage, const int penetration, const float shotDelay, const float range, const float projectileSpeed,
	const int ammoCapacity, const float reloadTime, const Texture& projectileTexture)
{
	this->isMelee = false;


	this->ID = ID;
	this->damage = damage;
	this->penetration = penetration;
	this->shotDelay = shotDelay;
	this->range = range;
	this->projectileSpeed = projectileSpeed;
	this->currentAmmo = this->ammoCapacity = ammoCapacity;
	this->reloadTime = reloadTime;
	this->projectileTexture = &projectileTexture;
}


void Weapon::action(vector<Projectile>& projectiles, const gameObject& projectileSource, const Clock& clock)
{
							//delay between shots or swings					//out of ammo (ranged)
	if (clock.getElapsedTime().asSeconds() - latestShotTime < shotDelay or (!isMelee and !currentAmmo))
		return;

	if (this->isMelee)
	{
		Projectile hitbox(penetration, clock.getElapsedTime().asSeconds(), projectileLifetime, hitboxPositions);

		//debug
		hitbox.body.setFillColor(Color::White);
		hitbox.body.setSize(hitboxSize);
		hitbox.body.setPosition(this->hitboxPositions.at(0));
		
		//time
		latestShotTime = hitbox.creationTime;

		projectiles.push_back(hitbox);
	}
	else
	{
		currentAmmo--;

		Projectile projectile(penetration, range);

		//tech
		projectile.currentDirection = projectileSource.currentSight;
		projectile.body.setPosition(projectileSource.body.getPosition());

		//gO stuff
		projectile.basespeed = projectile.speed = projectileSpeed;
		projectile.body.setSize(Vector2f{ projectileTexture->getSize() });
		projectile.body.setTexture(projectileTexture);

		//default rotation is ---->0
		if (projectile.currentDirection == Vector2f(0, -1))
			projectile.body.setRotation(-90);
		else if (projectile.currentDirection == Vector2f(0, 1))
			projectile.body.setRotation(90);
		else if (projectile.currentDirection == Vector2f(-1, 0))
			projectile.body.setRotation(180);
		else
		{
			projectile.body.setRotation(double(atan2(projectile.currentDirection.y, projectile.currentDirection.x)) * 180 / 3.14);
		}

		//time
		latestShotTime = clock.getElapsedTime().asSeconds();

		projectiles.push_back(projectile);
	}
}


//calling clock internally instead of getting elapsed time is cheaper
//because not every call meets first condition
void Weapon::reloadHandle(const Clock& clock)
{
	if (!currentAmmo and !isMelee)
	{
		float elapsedTime = clock.getElapsedTime().asSeconds();

		if (!latestReloadUpdate) //skips 1 call of lRU == elapsedTime
		{
			latestReloadUpdate = elapsedTime;
			return;
		}

		reloadTimer += elapsedTime - latestReloadUpdate;
		latestReloadUpdate = elapsedTime;
		if (reloadTimer > reloadTime)
		{
			currentAmmo = ammoCapacity;
			reloadTimer = 0;
			latestReloadUpdate = 0;
		}
	}
}

