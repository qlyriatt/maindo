#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

//CLASS DEFINING EVERYTHING YOU CAN SEE ON SCREEN

class gameObject 
{
public:
	
	gameObject();
	
	gameObject(float, bool, short int, Vector2f, Vector2f, Color, float); //should be removed later
	
	gameObject(float, bool, short int, Vector2f, Texture);

	gameObject(float, Vector2f, Texture);

	bool collision_check(RectangleShape, Vector2f);

	bool collision_check(FloatRect, Vector2f);

	bool collision_check(gameObject, Vector2f);

	void collision_check_inner(FloatRect);

	RectangleShape getbody();

	float getspeed();

	float getbasespeed();

	void setspeed(float);

	Vector2f getcenter();		//
								//needs merging
	Vector2f getcenter(int);	//

	void move(Vector2f);
	//be careful
	virtual Vector2f getdirection();


	RectangleShape body; //remove
	
	
	float basespeed, speed;
	bool allowCollision;
	short int interactionType;
	
	float interactionRadius = 5;
	Sprite sprite;
};
