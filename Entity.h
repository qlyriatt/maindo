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

	Vector2f getcenter();
	void move(Vector2f);



	/// <summary>
	/// Checks collision with outside objects i.e. when an entity tries to go inside an obstacle
	/// </summary>
	/// <param name="Obstacle">
	/// </param>
	void collision_check(RectangleShape);

	void collision_check_inner(FloatRect);

	//void shiftPosition(float x, float y);

	//void fire();

	//void interactive();

};




