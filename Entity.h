#pragma once
#include  <SFML/Graphics.hpp>
#include "gameObject.h"


class Entity : public gameObject
{
protected:
	
	RectangleShape body;
	
	float basespeed, speed;


public:
	
	Entity();
	Entity(float, float, float, float, float);

	RectangleShape getbody();

	float getspeed();
	float getbasespeed();
	void setspeed(float);

	Vector2f getcenter();

	/////////////////////////////////////
	virtual Vector2f getdirection()
	{
		return Vector2f(0,0);
	};
	

	void move(Vector2f);



	/// <summary>
	/// Checks collision outside i.e. when an entity tries to go inside an obstacle
	/// </summary>
	void collision_check(RectangleShape, Vector2f);

	/// <summary>
	/// Checks collision within i.e. when an entity tries to go outside of an area
	/// </summary>
	void collision_check_inner(FloatRect);

};




