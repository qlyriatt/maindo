#include "gameObject.h"
#include <iostream>

gameObject::gameObject()
{
	moving = false;
	baseSpeed = speed = 0;
	latestUpdate = 0;
	latestDistanceCovered = 0;
}

gameObject::~gameObject()
{

}

//should be removed later
gameObject::gameObject(float speed, Vector2f bodyPosition, Vector2f bodySize, bool allowCollision, Color bodyColor, Color outlineColor,
	float outlineThickness, short int interactionType, short int interactionRadius)
{
	//initial values
	
	this->speed = this->baseSpeed = speed;
	body.setPosition(bodyPosition);
	body.setSize(bodySize);
	this->allowCollision = allowCollision;
	body.setFillColor(bodyColor);
	body.setOutlineColor(outlineColor);
	body.setOutlineThickness(outlineThickness);
	this->interactionType = interactionType;
	this->interactionRadius = interactionRadius;

	// movement
	currentSight = Vector2f(1, 0);
	moving = false;
	latestUpdate = 0;
	latestDistanceCovered = 0;
}

gameObject::gameObject(float speed, Vector2f spritePosition, Texture* texture, bool allowCollision, int interactionType, int interactionRadius)
{
	//initial values
	
	this->speed = this->baseSpeed = speed;
	sprite.setPosition(spritePosition);
	sprite.setTexture(*texture);
	this->allowCollision = allowCollision;
	this->interactionType = interactionType;
	this->interactionRadius = interactionRadius;

	// compatibility

	body.setPosition(spritePosition);
	body.setSize(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
	body.setFillColor(Color::Transparent);

	// movement
	currentSight = Vector2f(1, 0);
	moving = false;
	latestUpdate = 0;
	latestDistanceCovered = 0;
}


//better FIX something else

bool gameObject::collisionCheck(gameObject obstacle)
{
	if (obstacle.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()))
	{
		if (obstacle.allowCollision)
			return true;

		Vector2f solution = -currentDirection * latestDistanceCovered;
		sprite.move(solution);
		body.move(solution);

		return true;
	}
	return false;
}

bool gameObject::collisionCheck(gameObject obstacle, int)
{
	if (obstacle.body.getGlobalBounds().intersects(body.getGlobalBounds()))
	{
		if (obstacle.allowCollision)
			return true;

		Vector2f solution = -currentDirection * latestDistanceCovered;
		sprite.move(solution);
		body.move(solution);

		return true;
	}
	
	return false;
}

void gameObject::collisionCheckInner(FloatRect area)
{
	bool TL = area.contains(sprite.getPosition());
	bool TR = area.contains(sprite.getPosition() + Vector2f(sprite.getGlobalBounds().width,0));
	bool BL = area.contains(sprite.getPosition() + Vector2f(0,sprite.getGlobalBounds().height));
	bool BR = area.contains(sprite.getPosition() + Vector2f(sprite.getGlobalBounds().width,sprite.getGlobalBounds().height));

	if (!(TL and TR and BR and BL))
	{
		Vector2f solution = -currentDirection * latestDistanceCovered;
		sprite.move(solution);
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
	if (!(moving and speed))
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
	sprite.move(distance);
}

void gameObject::script(int type, Vector2f node, Vector2f playerPosition, float elapsedTime)
{
	srand(elapsedTime);
	Vector2f offset = node - body.getPosition();
	Vector2f offsetPlayer = playerPosition - body.getPosition();
	
	bool movenode = false;
	if (sqrt(offset.x * offset.x + offset.y * offset.y) > 250 or (movedToNode > 0 and movedToNode < 2))
	{
		movenode = true;
		moving = true;
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
		moving = true;
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
			moving = false;
		}
		else
		{
			moving = true;
		}
	}
	else
	{
		latestmove = 0;
	}

	updatePosition(elapsedTime);
}

