#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Weapon
{
public:
	Weapon();

	void action(Vector2f sightDirection, RenderWindow*, Vector2f shotPosition);
	float range, damage, type, fireRate, projectileSpeed;
	Vector2f projectilePosition, shotPosition;
	bool has_fired;

private:
};

