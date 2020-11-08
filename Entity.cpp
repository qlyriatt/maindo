#include "Entity.h"




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
