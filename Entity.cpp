#include "Entity.h"

Entity::Entity() : gameObject()
{
	type = 0;
}

Entity::Entity(int type, Vector2f position, Vector2f size, Texture* texture, float speed, bool allowCollision,
	Color bodyColor, Color outlineColor, float outlineThickness) : gameObject(position, size, texture, speed, allowCollision, bodyColor, outlineColor, outlineThickness)
{
	this->type = type;
}

void Entity::script(Vector2f node, Vector2f playerPosition, float elapsedTime, std::vector<Projectile>* projectiles)
{
	srand(elapsedTime);
	Vector2f offset = node - body.getPosition();
	Vector2f offsetPlayer = playerPosition - body.getPosition();

	bool movenode = false;
	if (sqrt(offset.x * offset.x + offset.y * offset.y) > 250 or (movedToNode > 0 and movedToNode < 2))
	{
		movenode = true;
		isMoving = true;
		movingSwitch = 0;
		body.setFillColor(Color(20, 20, 200));
		if (offset.y == 0)
			offset.y = 5;
		if (offset.x == 0)
			offset.x = 5;
		float tan = offset.y / offset.x;
		// x*x + y*y = 1
		if ((offset.x > 0 and offset.y > 0) or (offset.x > 0 and offset.y < 0))
		{
			currentDirection.x = sqrt(1 / (1 + tan * tan));
		}
		else
		{
			currentDirection.x = -sqrt(1 / (1 + tan * tan));
		}
		currentDirection.y = tan * currentDirection.x;
		movedToNode += elapsedTime - latestUpdate;
	}
	bool moveplayer = false;
	if (sqrt(offsetPlayer.x * offsetPlayer.x + offsetPlayer.y * offsetPlayer.y) < 200 and !movenode)
	{
		moveplayer = true;
		movedToNode = 0;
		isMoving = true;
		movingSwitch = 0;
		body.setFillColor(Color(150, 20, 20));
		if (offsetPlayer.y == 0)
			offsetPlayer.y = 5;
		if (offsetPlayer.x == 0)
			offsetPlayer.x = 5;
		float tan = offsetPlayer.y / offsetPlayer.x;
		// x*x + y*y = 1
		if ((offsetPlayer.x > 0 and offsetPlayer.y > 0) or (offsetPlayer.x > 0 and offsetPlayer.y < 0))
		{
			currentDirection.x = sqrt(1 / (1 + tan * tan));
		}
		else
		{
			currentDirection.x = -sqrt(1 / (1 + tan * tan));
		}
		currentDirection.y = tan * currentDirection.x;
		weapon.action(currentDirection, body.getPosition(), elapsedTime, projectiles);
	}

	if (!movenode and !moveplayer)
	{
		movedToNode = 0;
		body.setFillColor(Color(150, 150, 150));
		int angle = rand() % 360;
		float t = tan(angle);
		if (angle > 180)
			currentDirection.x = sqrt(1 / (1 + t * t));
		else
			currentDirection.x = -sqrt(1 / (1 + t * t));
		currentDirection.y = t * currentDirection.x;

		movingSwitch = 1;
	}

	if (movingSwitch)
	{
		latestmove += elapsedTime;
		if (int(floor(latestmove)) % 2)
		{
			isMoving = false;
		}
		else
		{
			isMoving = true;
		}
	}
	else
	{
		latestmove = 0;
	}

	updatePosition(elapsedTime);

}