#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class gameObjectStationary
{
protected:
	~gameObjectStationary();
public:

	gameObjectStationary();

	gameObjectStationary(Vector2f position, Vector2f size, const Texture* texture = NULL, bool allowCollision = false, 
		Color bodyColor = Color::Black, Color outlineColor = Color::Red, float outlineThickness = 4);

	const Vector2f getCenter() const;

	virtual void updateAnimation(float elapsedTime, const Texture* texture, int animationCycles);


	bool	isDestroyable;
	bool	isAnimated;
	bool	allowCollision;
	int		interactionType;
	int		interactionTypeSpeciality;
	float	animationCycleTimer;
	float	latestAnimationUpdate;
	float	interactionRadius;
	mutable RectangleShape body;
};