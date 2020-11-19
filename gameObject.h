#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

//CLASS DEFINING EVERYTHING YOU CAN SEE ON SCREEN

class gameObject 
{
public:
	
	gameObject();
	
	gameObject(float speed, Vector2f bodyPosition, Vector2f bodySize, bool allowCollision = 0, Color outlineColor = Color::Red, float outlineThickness = 4,
		 short int interactionType = 0); //should be removed later
	
	gameObject(float speed, Vector2f spritePosition, Texture* texture, bool allowCollision = 0, short int interactionType = 0,
		Vector2f bodyPosition = Vector2f(0, 0), Color bodyColor = Color::White, float bodyOutlineThickness = 0);

	bool collision_check(RectangleShape, Vector2f); //should be removed

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
