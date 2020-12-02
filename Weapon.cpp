#include "Weapon.h"


Weapon::Weapon()
{
	range = damage = fireRate = projectileSpeed = latestShotTime = projectilePenetration = 0;
	projectileTexture = NULL;
}

Weapon::Weapon(float range, float projectileSpeed, Texture* weaponTexture, Texture* projectileTexture, float fireRate, float damage)
{
	this->latestShotTime = 0;

	this->projectilePenetration = 2;

	this->range = range;

	this->projectileSpeed = projectileSpeed;

	this->fireRate = fireRate;

	this->damage = damage;

	this->body.setTexture(weaponTexture);

	this->projectileTexture = projectileTexture;
}

void Weapon::action(Vector2f shotDirection, Vector2f shotPosition, float elapsedTime, std::vector<Projectile>* projectiles)
{
	if (fireRate == 0)
		return;
	if (elapsedTime - latestShotTime < 1 / fireRate)	//firerate is shots per second
		return;
	else
	{
		latestShotTime = elapsedTime;

		Projectile projectile;

		projectile.penetration = this->projectilePenetration;

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