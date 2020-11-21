#include "Weapon.h"
#include "Player.h"


Weapon::Weapon()
{
	range = damage = type = fireRate = projectileSpeed = has_fired = 0;
	projectilePosition = shotPosition = Vector2f(0, 0);
}


Projectile Weapon::action(Vector2f sightDirection, Vector2f shotPosition)
{
	Projectile projectile;

	projectile.projectile.body.setSize(Vector2f(10, 3));
	projectile.projectile.body.setFillColor(Color(Color::Red));
	projectile.projectile.speed = this->projectileSpeed;
	projectile.range = this->range;
	projectile.shotDirection = sightDirection;
	projectile.projectile.body.setPosition(shotPosition);
	projectile.currentPosition = Vector2f(0, 0);

	//for (; sqrt(projectilePosition.x*projectilePosition.x + projectilePosition.y * projectilePosition.y) < range;)
	//{
	//	projectilePosition += sightDirection * projectileSpeed;
	//	projectile.setPosition(shotPosition + projectilePosition);
	//	window->draw(projectile);
	//	window->display();
	//}

	return projectile;
	//if (!has_fired)
	//{
	//	projectilePosition = shotPosition;
	//	this->shotPosition = shotPosition;
	//	has_fired = 1;
	//}

	//if (sqrt((projectilePosition.x - shotPosition.x) * (projectilePosition.x - shotPosition.x) + (projectilePosition.y - shotPosition.y)*(projectilePosition.y - shotPosition.y)) < range)
	//{
	//	projectilePosition += sightDirection * projectileSpeed;
	//	projectile.setPosition(projectilePosition);

	//	window->draw(projectile);
	//}
	//else
	//{
	//	has_fired = 0;
	//	projectilePosition = Vector2f(0, 0);
	//}
	
}