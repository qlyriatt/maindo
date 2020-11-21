#include "gameObject.h"

gameObject::gameObject()
{
	allowCollision = interactionRadius = interactionType = speed = baseSpeed = 0;
}

gameObject::~gameObject()
{

}

gameObject::gameObject(float speed, Vector2f bodyPosition, Vector2f bodySize, bool allowCollision, Color bodyColor, Color outlineColor,
	float outlineThickness, short int interactionType, short int interactionRadius)
{
	this->speed = this->baseSpeed = speed;
	body.setPosition(bodyPosition);
	body.setSize(bodySize);
	this->allowCollision = allowCollision;
	body.setFillColor(bodyColor);
	body.setOutlineColor(outlineColor);
	body.setOutlineThickness(outlineThickness);
	this->interactionType = interactionType;
	this->interactionRadius = interactionRadius;
} //should be removed later

gameObject::gameObject(float speed, Vector2f spritePosition, Texture* texture, bool allowCollision, int interactionType, int interactionRadius)
{
	this->speed = this->baseSpeed = speed;
	sprite.setPosition(spritePosition);
	sprite.setTexture(*texture);
	this->allowCollision = allowCollision;
	this->interactionType = interactionType;
	this->interactionRadius = interactionRadius;

	body.setPosition(spritePosition);
	body.setSize(Vector2f(sprite.getGlobalBounds().width,sprite.getGlobalBounds().height));
}

Vector2f gameObject::getCenter()
{
	return Vector2f(body.getPosition() + body.getSize() / 2.f);
}

Vector2f gameObject::getCenter(int)
{
	return Vector2f(sprite.getPosition() + Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2));
}

void gameObject::move(Vector2f direction)
{
	body.move(direction);
}

void gameObject::move(Vector2f direction, int)
{
	sprite.move(direction);
}

Vector2f gameObject::getDirection()
{
	return Vector2f(0, 0);
}


//whoops --N-- hours of life are now gone
//
///////////////////////////   FIX THIS
//
// Player stops when going to the older object from the newer one while colliding with them both at the same time
// (EXAMPLE --- when you try to go into UP into 2 walls and LEFT simultaniosly)
//
bool gameObject::collision_check(RectangleShape obstacle, Vector2f direction)
{
	if (obstacle.getGlobalBounds().intersects(sprite.getGlobalBounds()))
	{
		if (direction == Vector2f(0, -1)) //UP
		{
			sprite.move(0, speed);
		}
		else if (direction == Vector2f(1, -1)) //UP RIGHT
		{
			sprite.move(0, speed);
			if (obstacle.getGlobalBounds().intersects(sprite.getGlobalBounds()))
				sprite.move(-speed, -speed);
			else
			{
				sprite.move(-speed, -speed);
				if (obstacle.getGlobalBounds().intersects(sprite.getGlobalBounds()))
					sprite.move(speed, speed);
			}
		}
		else if (direction == Vector2f(1, 0)) //RIGHT
		{
			sprite.move(-speed, 0);
		}
		else if (direction == Vector2f(1, 1)) //DOWN RIGHT
		{
			sprite.move(0, -speed);
			if (obstacle.getGlobalBounds().intersects(sprite.getGlobalBounds()))
				sprite.move(-speed, speed);
			else
			{
				sprite.move(-speed, speed);
				if (obstacle.getGlobalBounds().intersects(sprite.getGlobalBounds()))
					sprite.move(speed, -speed);
			}
		}
		else if (direction == Vector2f(0, 1)) //DOWN
		{
			sprite.move(0, -speed);
		}
		else if (direction == Vector2f(-1, 1)) //DOWN LEFT
		{
			sprite.move(0, -speed);
			if (obstacle.getGlobalBounds().intersects(sprite.getGlobalBounds()))
				sprite.move(speed, speed);
			else
			{
				sprite.move(speed, speed);
				if (obstacle.getGlobalBounds().intersects(sprite.getGlobalBounds()))
					sprite.move(-speed, -speed);
			}
		}
		else if (direction == Vector2f(-1, 0)) //LEFT
		{
			sprite.move(speed, 0);
		}
		else if (direction == Vector2f(-1, -1)) //UP LEFT
		{
			sprite.move(0, speed);
			if (obstacle.getGlobalBounds().intersects(sprite.getGlobalBounds()))
				sprite.move(speed, -speed);
			else
			{
				sprite.move(speed, -speed);
				if (obstacle.getGlobalBounds().intersects(sprite.getGlobalBounds()))
					sprite.move(-speed, speed);
			}
		}
		return true;
	}
	return false;
} //should be removed AND fixed

bool gameObject::collision_check(FloatRect obstacle, Vector2f direction)
{
	if (obstacle.intersects(sprite.getGlobalBounds()))
	{
		if (direction == Vector2f(0, -1)) //UP
		{
			sprite.move(0, speed);
		}
		else if (direction == Vector2f(1, -1)) //UP RIGHT
		{
			sprite.move(0, speed);
			if (obstacle.intersects(sprite.getGlobalBounds()))
				sprite.move(-speed, -speed);
			else
			{
				sprite.move(-speed, -speed);
				if (obstacle.intersects(sprite.getGlobalBounds()))
					sprite.move(speed, speed);
			}
		}
		else if (direction == Vector2f(1, 0)) //RIGHT
		{
			sprite.move(-speed, 0);
		}
		else if (direction == Vector2f(1, 1)) //DOWN RIGHT
		{
			sprite.move(0, -speed);
			if (obstacle.intersects(sprite.getGlobalBounds()))
				sprite.move(-speed, speed);
			else
			{
				sprite.move(-speed, speed);
				if (obstacle.intersects(sprite.getGlobalBounds()))
					sprite.move(speed, -speed);
			}
		}
		else if (direction == Vector2f(0, 1)) //DOWN
		{
			sprite.move(0, -speed);
		}
		else if (direction == Vector2f(-1, 1)) //DOWN LEFT
		{
			sprite.move(0, -speed);
			if (obstacle.intersects(sprite.getGlobalBounds()))
				sprite.move(speed, speed);
			else
			{
				sprite.move(speed, speed);
				if (obstacle.intersects(sprite.getGlobalBounds()))
					sprite.move(-speed, -speed);
			}
		}
		else if (direction == Vector2f(-1, 0)) //LEFT
		{
			sprite.move(speed, 0);
		}
		else if (direction == Vector2f(-1, -1)) //UP LEFT
		{
			sprite.move(0, speed);
			if (obstacle.intersects(sprite.getGlobalBounds()))
				sprite.move(speed, -speed);
			else
			{
				sprite.move(speed, -speed);
				if (obstacle.intersects(sprite.getGlobalBounds()))
					sprite.move(-speed, speed);
			}
		}
		return true;
	}
	return false;
} //should be removed AND fixed

//replace "body" with "sprite"
bool gameObject::collision_check(gameObject obstacle, Vector2f direction)
{
	if (obstacle.body.getGlobalBounds().intersects(sprite.getGlobalBounds()))
	{
		if (obstacle.allowCollision)
			return true;

		if (direction == Vector2f(0, -1)) //UP
		{
			sprite.move(0, speed);
		}
		else if (direction == Vector2f(1, -1)) //UP RIGHT
		{
			sprite.move(0, speed);
			if (obstacle.body.getGlobalBounds().intersects(sprite.getGlobalBounds()))
				sprite.move(-speed, -speed);
			else
			{
				sprite.move(-speed, -speed);
				if (obstacle.body.getGlobalBounds().intersects(sprite.getGlobalBounds()))
					sprite.move(speed, speed);
			}
		}
		else if (direction == Vector2f(1, 0)) //RIGHT
		{
			sprite.move(-speed, 0);
		}
		else if (direction == Vector2f(1, 1)) //DOWN RIGHT
		{
			sprite.move(0, -speed);
			if (obstacle.body.getGlobalBounds().intersects(sprite.getGlobalBounds()))
				sprite.move(-speed, speed);
			else
			{
				sprite.move(-speed, speed);
				if (obstacle.body.getGlobalBounds().intersects(sprite.getGlobalBounds()))
					sprite.move(speed, -speed);
			}
		}
		else if (direction == Vector2f(0, 1)) //DOWN
		{
			sprite.move(0, -speed);
		}
		else if (direction == Vector2f(-1, 1)) //DOWN LEFT
		{
			sprite.move(0, -speed);
			if (obstacle.body.getGlobalBounds().intersects(sprite.getGlobalBounds()))
				sprite.move(speed, speed);
			else
			{
				sprite.move(speed, speed);
				if (obstacle.body.getGlobalBounds().intersects(sprite.getGlobalBounds()))
					sprite.move(-speed, -speed);
			}
		}
		else if (direction == Vector2f(-1, 0)) //LEFT
		{
			sprite.move(speed, 0);
		}
		else if (direction == Vector2f(-1, -1)) //UP LEFT
		{
			sprite.move(0, speed);
			if (obstacle.body.getGlobalBounds().intersects(sprite.getGlobalBounds()))
				sprite.move(speed, -speed);
			else
			{
				sprite.move(speed, -speed);
				if (obstacle.body.getGlobalBounds().intersects(sprite.getGlobalBounds()))
					sprite.move(-speed, speed);
			}
		}
		return true;
	}
	return false;
}

void gameObject::collision_check_inner(FloatRect area)
{
	bool TL = area.contains(sprite.getPosition());
	bool TR = area.contains(sprite.getPosition() + Vector2f(sprite.getGlobalBounds().width,0));
	bool BL = area.contains(sprite.getPosition() + Vector2f(0,sprite.getGlobalBounds().height));
	bool BR = area.contains(sprite.getPosition() + Vector2f(sprite.getGlobalBounds().width,sprite.getGlobalBounds().height));

	if (!(TL and TR and BR and BL))
	{
		if (TL)
		{
			if (BL)
				sprite.move(-speed, 0);
			else if (TR)
				sprite.move(0, -speed);
			else
				sprite.move(-speed, -speed);
		}

		else if (BR)
		{
			if (TR)
				sprite.move(speed, 0);
			else if (BL)
				sprite.move(0, speed);
			else
				sprite.move(speed, speed);
		}

		else if (BL)
			sprite.move(-speed, speed);
		else if (TR)
			sprite.move(speed, -speed);
	}
}
