#pragma once
#include  <SFML/Graphics.hpp>
#include <iostream>
#include "gameObject.h"
//#include "Weapon.h"


using namespace std;
using namespace sf;

class Entity : public gameObject
{
protected:
	
	RectangleShape body;
	
	float basespeed, speed;

	//string name;

	//uint8_t healthPoints;

	//Weapon *Weapons;


public:
	
	Entity()
	{
		body.setSize(Vector2f(0, 0));
		body.setPosition(0, 0);
		speed = basespeed = 0;
	};
	Entity(float, float, float, float, float);

	RectangleShape getbody();

	float getspeed();
	float getbasespeed();
	void setspeed(float);

	//void shiftPosition(float x, float y);

	//void fire();

	//void interactive();

	//void collisionCheck(RectangleShape *mapBounds, float *time);
};


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