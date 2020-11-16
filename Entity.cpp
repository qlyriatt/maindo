#include "Entity.h"
#include <iostream>


Entity::Entity()
{
	body.setSize(Vector2f(0, 0));
	body.setPosition(0, 0);
	speed = basespeed = 0;
}

Entity::Entity(float width, float height, float xpos, float ypos, float speed)
{
	Vector2f size(width, height);
	body.setSize(size);
	body.setPosition(xpos, ypos);
	this->speed = basespeed = speed;
}

//Get entity shape object
RectangleShape Entity::getbody()
{
	return body;
}

//Get entity speed
float Entity::getspeed()
{
	return speed;
}

//Get base entity speed
float Entity::getbasespeed()
{
	return basespeed;
}

//Set entity speed
void Entity::setspeed(float speed)
{
	this->speed = speed;
}

Vector2f Entity::getcenter()
{
	return Vector2f(body.getPosition() + body.getSize() / 2.f);
}

void Entity::move(Vector2f direction)
{
	body.move(direction);
}

//whoops --N-- hours of life are now gone
///////////////////////////   FIX THIS
//
// Player stops when going to the older object from the newer one while colliding with them both at the same time
// (EXAMPLE --- when you try to go into UP into 2 walls and LEFT simultaniosly)
//
void Entity::collision_check(RectangleShape obstacle, Vector2f direction)
{
	if (obstacle.getGlobalBounds().intersects(body.getGlobalBounds()))
	{
		if (direction == Vector2f(0,-1)) //UP
		{
			body.move(0, speed);
		}
		else if (direction == Vector2f(1, -1)) //UP RIGHT
		{
			body.move(0, speed);
			if (obstacle.getGlobalBounds().intersects(body.getGlobalBounds()))
				body.move(-speed, -speed);
			else
			{
				body.move(-speed, -speed);
				if (obstacle.getGlobalBounds().intersects(body.getGlobalBounds()))
					body.move(speed, speed);
			}
		}
		else if (direction == Vector2f(1, 0)) //RIGHT
		{
			body.move(-speed, 0);
		}
		else if (direction == Vector2f(1, 1)) //DOWN RIGHT
		{
			body.move(0, -speed);
			if (obstacle.getGlobalBounds().intersects(body.getGlobalBounds()))
				body.move(-speed, speed);
			else
			{
				body.move(-speed, speed);
				if (obstacle.getGlobalBounds().intersects(body.getGlobalBounds()))
					body.move(speed, -speed);
			}
		}
		else if (direction == Vector2f(0, 1)) //DOWN
		{
			body.move(0, -speed);
		}
		else if (direction == Vector2f(-1, 1)) //DOWN LEFT
		{
			body.move(0, -speed);
			if (obstacle.getGlobalBounds().intersects(body.getGlobalBounds()))
				body.move(speed, speed);
			else
			{
				body.move(speed, speed);
				if (obstacle.getGlobalBounds().intersects(body.getGlobalBounds()))
					body.move(-speed, -speed);
			}
		}
		else if (direction == Vector2f(-1, 0)) //LEFT
		{
			body.move(speed, 0);
		}
		else if (direction == Vector2f(-1, -1)) //UP LEFT
		{						
			body.move(0, speed);
			if (obstacle.getGlobalBounds().intersects(body.getGlobalBounds()))
				body.move(speed, -speed);
			else
			{
				body.move(speed, -speed);
				if (obstacle.getGlobalBounds().intersects(body.getGlobalBounds()))
					body.move(-speed, speed);
			}			
		}
	}
}

void Entity::collision_check_inner(FloatRect area)
{
	bool TL = area.contains(body.getPosition() + body.getPoint(0));
	bool TR = area.contains(body.getPosition() + body.getPoint(1));
	bool BR = area.contains(body.getPosition() + body.getPoint(2));
	bool BL = area.contains(body.getPosition() + body.getPoint(3));

	if (!(TL and TR and BR and BL))
	{
		if (TL)
		{
			if (BL)
				body.move(-speed, 0);
			else if (TR)
				body.move(0, -speed);
			else
				body.move(-speed, -speed);
		}

		else if (BR)
		{
			if (TR)
				body.move(speed, 0);
			else if (BL)
				body.move(0, speed);
			else
				body.move(speed, speed);
		}

		else if (BL)
			body.move(-speed, speed);
		else if (TR)
			body.move(speed, -speed);
	}


}

