#include "gameObject.h"

gameObject::gameObject()
{
	allowCollision = interactionType = basespeed = speed = 0;
}

gameObject::gameObject(float speed, bool allowCollision, short int interactionType, Vector2f position, Vector2f size, Color color, float outline) 
{
	body.setPosition(position);
	body.setSize(size);
	body.setFillColor(color);
	body.setOutlineThickness(outline);
	
	this->basespeed = this->speed = speed;
	this->interactionType = interactionType;
	this->allowCollision = allowCollision;
} //should be removed later

gameObject::gameObject(float speed, bool allowCollision, short int interactionType, Vector2f position, Texture texture)
{
	this->basespeed = this->speed = speed;
	this->interactionType = interactionType;
	this->allowCollision = allowCollision;
	sprite.setTexture(texture);
}

gameObject::gameObject(float speed, Vector2f position, Texture texture)
{
	this->basespeed = this->speed = speed;
	this->interactionType = 0;
	this->allowCollision = 0;
	sprite.setTexture(texture);
	sprite.setPosition(position);
}

RectangleShape gameObject::getbody()
{
	return body;
}

float gameObject::getspeed()
{
	return speed;
}

float gameObject::getbasespeed()
{
	return basespeed;
}

void gameObject::setspeed(float speed)
{
	this->speed = speed;
}

Vector2f gameObject::getcenter()
{
	return Vector2f(body.getPosition() + body.getSize() / 2.f);
}

Vector2f gameObject::getcenter(int)
{
	return Vector2f(sprite.getPosition() + Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2));
}

void gameObject::move(Vector2f direction)
{
	body.move(direction);
}

Vector2f gameObject::getdirection()
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
