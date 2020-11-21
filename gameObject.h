#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

//CLASS DEFINING EVERYTHING YOU CAN SEE ON SCREEN

class gameObject 
{
public:
	
	gameObject();
	
	virtual ~gameObject();

	gameObject(float speed, Vector2f bodyPosition, Vector2f bodySize, bool allowCollision = 0, Color bodyColor = Color::Black, Color outlineColor = Color::Red, float outlineThickness = 4,
		 short int interactionType = 0, short int interactionRadius = 5); //easier, without a sprite //should be removed later
	
	gameObject(float speed, Vector2f spritePosition, Texture* texture, bool allowCollision = 0, int interactionType = 0, int interactionRadius = 0);

	bool collision_check(RectangleShape, Vector2f); //should be removed

	bool collision_check(FloatRect, Vector2f);

	bool collision_check(gameObject, Vector2f);

	void collision_check_inner(FloatRect); //somewhat excessive (though probably not...)

	////////////////////////////// INT FUNCTIONS WORK WITH SPRITES
	Vector2f getCenter();		//
								//needs merging
	Vector2f getCenter(int);	//

	void move(Vector2f);		//
								//needs merging
	void move(Vector2f, int);	//

	//be careful
	virtual Vector2f getDirection(); //redefines in player class

	//////////////////////////////////////////////////////////////////////////////////////////

	RectangleShape body; //should be removed                //...or maybe not
	
	float baseSpeed; //useful for something 

	float speed; //speed is key

	bool allowCollision;

	int interactionType;
	
	float interactionRadius;
	
	Sprite sprite;
};
