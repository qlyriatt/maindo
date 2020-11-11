#include "Entity.h"

//#define RIGHT basespeed
//#define DOWN basespeed
//#define LEFT -RIGHT
//#define UP -DOWN


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

void Entity::move(Vector2f action)
{
	body.move(action);
}

void Entity::collision_check(RectangleShape obstacle)
{
	bool TL = obstacle.getGlobalBounds().contains(body.getPosition() + body.getPoint(0));
	bool TR = obstacle.getGlobalBounds().contains(body.getPosition() + body.getPoint(1));
	bool BR = obstacle.getGlobalBounds().contains(body.getPosition() + body.getPoint(2));
	bool BL = obstacle.getGlobalBounds().contains(body.getPosition() + body.getPoint(3));


	if (TL or TR or BR or BL)
	{
		if (TL)
		{
			if (BL)
				body.move(speed, 0);
			else if (TR)
				body.move(0, speed);
			//if move(speed, 0) i.e. MOVE RIGHT clears collision before checking TL a second time
			//entity performs a jump equal to speed -----> 
			//this reflects in it going around the corner which can be undesirable
			//the effect is present for every type of one point collision
			//
			//
			//      //////			//////
			//		//////	--->	//////
			//		//////			//////*\*
			//			 *\*		
			//
			// (or apparently it won't)
			else
			{
				body.move(speed, 0);
				TL = obstacle.getGlobalBounds().contains(body.getPosition() + body.getPoint(0));
				if (TL)
					body.move(-speed, speed);
			}
		}

		else if (BR)
		{
			if (BL)
				body.move(0, -speed);
			else if (TR)
				body.move(-speed, 0);
			else
			{
				body.move(-speed, 0);
				BR = obstacle.getGlobalBounds().contains(body.getPosition() + body.getPoint(2));
				if (BR)
					body.move(speed, -speed);
			}
		}

		else if (TR)
		{
			body.move(-speed, 0);
			TR = obstacle.getGlobalBounds().contains(body.getPosition() + body.getPoint(1));
			if (TR)
				body.move(speed, speed);
		}

		else if (BL)
		{
			body.move(speed, 0);
			BL = obstacle.getGlobalBounds().contains(body.getPosition() + body.getPoint(3));
			if (BL)
				body.move(-speed, -speed);
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