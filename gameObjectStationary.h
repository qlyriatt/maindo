#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
#include <math.h>

class gameObjectStationary
{
protected:
	gameObjectStationary() {};
public:

	virtual ~gameObjectStationary() {};


	// basic initializer with only one texture state
	gameObjectStationary(const Vector2f& position, const Texture& texture);
	
	// initializer for testing, uses basic shapes without textures
	gameObjectStationary(const Vector2f& position, const Vector2f& size, 
		const int interactionType = 0, const int interactionTypeSpeciality = 0, const bool allowCollision = false);

	// final constructor
	gameObjectStationary(const Vector2f& position, const Texture& texture, const size_t animationStates, const bool allowCollision, 
		const bool isDestroyable, const int interactionType, const int interactionTypeSpeciality, const float interactionRadius = 10);

	Vector2f getCenter() const;

	virtual void updateAnimation(const float elapsedTime);


	//basic
	bool	isDestroyable = { false };
	bool	allowCollision = { false };
	RectangleShape body;
	Sprite	sprite;

	//interaction
	int		interactionType = { 0 };
	int		interactionTypeSpeciality = { 0 };
	float	interactionRadius = { 0 };

	//animation
	bool	isAnimated = { false };
	size_t	animationStates = { 0 };
	float	animationCycleTimer = { 0 };
	float	latestAnimationUpdate = { 0 };
};
