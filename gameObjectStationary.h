#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class gameObjectStationary
{
public:
	
	gameObjectStationary();

	gameObjectStationary(Vector2f position, Vector2f size, bool allowCollision = false, 
		Color bodyColor = Color::Black, Color outlineColor = Color::Red, float outlineThickness = 5);

	gameObjectStationary(Vector2f position, Texture* texture, bool allowCollision = false, int interactionType = 0, float interactionRadius = 5);

	Vector2f getCenter(bool spriteCenter = false);


	Sprite sprite;
	RectangleShape body; //to be removed
	bool allowCollision;
	int interactionType;
	float interactionRadius;
};