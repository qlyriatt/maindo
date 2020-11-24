#include "Weapon.h"


Weapon::Weapon()
{
	range = damage = type = fireRate = projectileSpeed = 0;
	projectileColor = Color::White;
	projectileTexture = NULL;
}

Weapon::Weapon(float range, float projectileSpeed, Color projectileColor, float fireRate, float damage, int weaponType, Texture* weaponTexture, Texture* projectileTexture)
{
	this->type = weaponType;
	this->range = range;
	this->projectileSpeed = projectileSpeed;
	this->fireRate = fireRate;
	this->damage = damage;
	this->projectileColor = projectileColor;

	//this->sprite.setTexture(*weaponTexture);
	this->projectileTexture = projectileTexture;
}

Projectile Weapon::action(Vector2f shotDirection, Vector2f shotPosition)
{
	Projectile projectile;

	projectile.body.setTexture(projectileTexture);
	projectile.body.setSize(Vector2f(10, 3));
	projectile.body.setFillColor(projectileColor);
	projectile.speed = this->projectileSpeed;
	projectile.range = this->range;
	projectile.currentDirection = shotDirection;
	projectile.currentPosition = Vector2f(0, 0);
	projectile.body.setPosition(shotPosition);
	projectile.sprite.setPosition(shotPosition);
	projectile.sprite.setTexture(*this->projectileTexture);
	projectile.moving = true;

	//default rotation is ---->0
	if (shotDirection == Vector2f(0, -1))
		projectile.sprite.setRotation(-90);
	else if (shotDirection == Vector2f(0, 1))
		projectile.sprite.setRotation(90);
	else if (shotDirection == Vector2f(-1, 0))
		projectile.sprite.setRotation(180);
	else
	{
		projectile.sprite.setRotation(atan2(shotDirection.y, shotDirection.x) * 180 / 3.14);
	}
	projectile.body.setRotation(projectile.sprite.getRotation());

	return projectile;
}