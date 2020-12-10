#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class gameObjectStationary
{
protected:
	~gameObjectStationary();
public:

	gameObjectStationary();

	gameObjectStationary(Vector2f position, Vector2f size, Texture* texture = NULL, bool allowCollision = false, 
		Color bodyColor = Color::Black, Color outlineColor = Color::Red, float outlineThickness = 4);

	Vector2f getCenter();

	virtual void updateAnimation(float elapsedTime, const Texture* texture, int animationCycles);


	bool isDestroyable;
	bool isAnimated;
	bool allowCollision;
	int interactionType;
	int interactionTypeSpeciality;
	float animationCycleTimer;
	float latestAnimationUpdate;
	float interactionRadius;
	RectangleShape body;
};