#include "gameObject.h"
#include <iostream>

gameObject::gameObject() : gameObjectStationary()
{
	isMoving = false;
	baseSpeed = speed = 0;
	latestUpdate = 0;
	latestDistanceCovered = 0;
}

gameObject::~gameObject()
{

}

gameObject::gameObject(Vector2f position, Vector2f size, Texture* texture, float speed,
	bool allowCollision, Color bodyColor, Color outlineColor, float outlineThickness) : gameObjectStationary(position, size, texture, allowCollision, bodyColor, outlineColor, outlineThickness)
{
	body.setTexture(texture);
	
	this->speed = this->baseSpeed = speed;

	currentSight = Vector2f(1, 0);

	isMoving = false;

	latestUpdate = 0;

	latestDistanceCovered = 0;
}


bool gameObject::collisionCheck(gameObject obstacle)
{
	if (obstacle.body.getGlobalBounds().intersects(body.getGlobalBounds()))
	{
		if (obstacle.allowCollision)
			return true;

		Vector2f solution = -currentDirection * latestDistanceCovered;
		body.move(solution);
		body.move(solution);

		return true;
	}
	return false;
}

void gameObject::collisionCheckInner(FloatRect area)
{
	bool TL = area.contains(body.getPosition());
	bool TR = area.contains(body.getPosition() + Vector2f(body.getGlobalBounds().width,0));
	bool BL = area.contains(body.getPosition() + Vector2f(0,body.getGlobalBounds().height));
	bool BR = area.contains(body.getPosition() + Vector2f(body.getGlobalBounds().width,body.getGlobalBounds().height));

	if (!(TL and TR and BR and BL))
	{
		Vector2f solution = -currentDirection * latestDistanceCovered;
		body.move(solution);
	}
}

//void gameObject::collisionCheckInner(FloatRect area)
//{
//	bool TL = area.contains(sprite.getPosition());
//	bool TR = area.contains(sprite.getPosition() + Vector2f(sprite.getGlobalBounds().width,0));
//	bool BL = area.contains(sprite.getPosition() + Vector2f(0,sprite.getGlobalBounds().height));
//	bool BR = area.contains(sprite.getPosition() + Vector2f(sprite.getGlobalBounds().width,sprite.getGlobalBounds().height));
//
//	if (!(TL and TR and BR and BL))
//	{
//		if (TL)
//		{
//			if (BL)
//				sprite.move(-speed, 0);
//			else if (TR)
//				sprite.move(0, -speed);
//			else
//				sprite.move(-speed, -speed);
//		}
//
//		else if (BR)
//		{
//			if (TR)
//				sprite.move(speed, 0);
//			else if (BL)
//				sprite.move(0, speed);
//			else
//				sprite.move(speed, speed);
//		}
//
//		else if (BL)
//			sprite.move(-speed, speed);
//		else if (TR)
//			sprite.move(speed, -speed);
//	}
//}

void gameObject::updatePosition(float elapsedTime)
{
	if (!(isMoving and speed))
	{
		latestUpdate = 0;
		return;
	}

	if (!latestUpdate)
	{
		latestUpdate = elapsedTime;
		return;
	}

	latestDistanceCovered = (elapsedTime - latestUpdate) * speed;
	Vector2f distance = currentDirection * latestDistanceCovered;
	latestUpdate = elapsedTime;
	body.move(distance);
}

void gameObject::script(Vector2f node, Vector2f playerPosition, float elapsedTime)
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
	if (sqrt(offsetPlayer.x * offsetPlayer.x + offsetPlayer.y * offsetPlayer.y) < 100 and !movenode)
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
	}

	if (!movenode and !moveplayer)
	{
		movedToNode = 0;
		body.setFillColor(Color(150, 150, 150));
		currentDirection.x = rand() % 2;
		currentDirection.y = rand() % 2;
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

