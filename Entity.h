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

	//be careful
	virtual Vector2f getdirection() = 0;
	

	void move(Vector2f);

	bool collision_check(RectangleShape, Vector2f);

	void collision_check_inner(FloatRect);

};




