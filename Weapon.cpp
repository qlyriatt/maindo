#include "Weapon.h"
#include "Player.h"


Weapon::Weapon()
{
	range = damage = type = fireRate = projectileSpeed = has_fired = 0;
	projectilePosition = shotPosition = Vector2f(0, 0);
}


void Weapon::action(Vector2f sightDirection, RenderWindow* window, Vector2f shotPosition)
{
	RectangleShape projectile;
	projectile.setSize(Vector2f(10, 10));
	projectile.setFillColor(Color(Color::Red));
	this->shotPosition = shotPosition;
	projectilePosition = Vector2f(0, 0);

	//sqrt((projectilePosition.x - this->shotPosition.x) * (projectilePosition.x - this->shotPosition.x) + (projectilePosition.y - this->shotPosition.y) * (projectilePosition.y - this->shotPosition.y)) < range
	for (; sqrt(projectilePosition.x*projectilePosition.x + projectilePosition.y * projectilePosition.y) < range;)
	{
		projectilePosition += sightDirection * projectileSpeed;
		projectile.setPosition(shotPosition + projectilePosition);
		window->draw(projectile);
		window->display();
	}

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