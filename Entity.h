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
	
	Entity();
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




