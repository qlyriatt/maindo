#include "Weapon.h"


Weapon::Weapon()
{
	ID = 0;
	range = damage = fireRate = projectileSpeed = latestShotTime = projectilePenetration = 0;
	isMelee = false;
	currentAmmo = ammoCapacity = latestReloadUpdate = reloadTime = reloadTimer = 0;
	projectileLifetime = 0;
	projectileTexture = NULL;
}

Weapon::Weapon(int ID, float range, float projectileSpeed, float ammoCapacity, Texture* projectileTexture, 
	float fireRate, float reloadTime, float damage)
{
	reloadTimer = latestReloadUpdate = isMelee = 0;

	this->ID = ID;
	
	this->projectileLifetime = 0;

	this->reloadTime = reloadTime;
	
	this->latestShotTime = 0;

	this->projectilePenetration = 0;

	this->range = range;

	this->projectileSpeed = projectileSpeed;

	this->fireRate = fireRate;

	this->damage = damage;

	this->projectileTexture = projectileTexture; 

	this->ammoCapacity = ammoCapacity;
	
	this->currentAmmo = ammoCapacity;
}

void Weapon::action(void* projectileSource, Vector2f shotDirection, Vector2f shotPosition, float elapsedTime, std::vector<Projectile>* projectiles)
{
	if (fireRate == 0)
		return;
	if (elapsedTime - latestShotTime < 1 / fireRate)	//firerate is shots per second
		return;
	
	Projectile projectile;

	projectile.isMelee = this->isMelee;

	projectile.penetration = this->projectilePenetration;

	projectile.gameObjectSource = projectileSource;

	projectile.lifeTime = this->projectileLifetime;

	projectile.creationTime = elapsedTime;

	projectile.weaponSource = this;

	if (isMelee)
	{
		latestShotTime = elapsedTime;
		//projectileSource->isUsingWeapon = true;
		projectile.body.setFillColor(Color::White);
		//projectile.body.setSize(projectileSource->body.getSize()); //<----
		projectile.body.setSize(hitboxSize);
		projectile.allowCollision = true;
		projectiles->push_back(projectile);
		return;
	}
	if (!currentAmmo)
	{
		if (!latestReloadUpdate)
		{
			latestReloadUpdate = elapsedTime;
			return;
		}

		reloadTimer += elapsedTime - latestReloadUpdate;
		latestReloadUpdate = elapsedTime;
		if (floor(reloadTime * 10) < floor(reloadTimer * 10))
		{
			currentAmmo = ammoCapacity;
			reloadTimer = 0;
			latestReloadUpdate = 0;
		}
	}
	else
	{	
		latestShotTime = elapsedTime;

		currentAmmo--;

		projectile.body.setTexture(projectileTexture);

		projectile.body.setSize(Vector2f(projectile.body.getTextureRect().width, projectile.body.getTextureRect().height));

		projectile.speed = this->projectileSpeed;

		projectile.range = this->range;

		projectile.currentDirection = shotDirection;

		projectile.currentPosition = Vector2f(0, 0);

		projectile.body.setPosition(shotPosition);

		projectile.isMoving = true;

		//default rotation is ---->0
		if (shotDirection == Vector2f(0, -1))
			projectile.body.setRotation(-90);
		else if (shotDirection == Vector2f(0, 1))
			projectile.body.setRotation(90);
		else if (shotDirection == Vector2f(-1, 0))
			projectile.body.setRotation(180);
		else
		{
			projectile.body.setRotation(atan2(shotDirection.y, shotDirection.x) * 180 / 3.14);
		}

		projectiles->push_back(projectile);
	}
}