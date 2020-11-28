#include "gameObjectStationary.h"

gameObjectStationary::gameObjectStationary()
{
	interactionType = 0;
	interactionRadius = 0;
	allowCollision = false;
}

gameObjectStationary::gameObjectStationary(Vector2f position, Vector2f size, Texture* texture, bool allowCollision, 
	Color bodyColor, Color outlineColor, float outlineThickness)
{
	body.setPosition(position);

	body.setSize(size);

	body.setTexture(texture, true);

	this->allowCollision = allowCollision;

	body.setFillColor(bodyColor);

	body.setOutlineColor(outlineColor);

	body.setOutlineThickness(outlineThickness);


	// later 
	this->interactionType = 0;
	this->interactionRadius = 5;
}

Vector2f gameObjectStationary::getCenter()
{
	return Vector2f(body.getPosition() + body.getSize() / 2.f);
}
