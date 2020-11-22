#include "gameObjectStationary.h"

gameObjectStationary::gameObjectStationary()
{
	interactionType = 0;
	interactionRadius = 0;
	allowCollision = false;
}

gameObjectStationary::gameObjectStationary(Vector2f position, Vector2f size, bool allowCollision, Color bodyColor, Color outlineColor, float outlineThickness)
{
	body.setPosition(position);
	body.setSize(size);
	this->allowCollision = allowCollision;
	body.setFillColor(bodyColor);
	body.setOutlineColor(outlineColor);
	body.setOutlineThickness(outlineThickness);
	this->interactionType = 0;
	this->interactionRadius = 5;
}

gameObjectStationary::gameObjectStationary(Vector2f position, Texture* texture, bool allowCollision, int interactionType, float interactionRadius)
{
	sprite.setPosition(position);
	sprite.setTexture(*texture);
	this->allowCollision = allowCollision;
	this->interactionType = interactionType;
	this->interactionRadius = interactionRadius;

	// compatibility

	body.setPosition(position);
	body.setSize(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
	body.setFillColor(Color::Transparent);
}

Vector2f gameObjectStationary::getCenter(bool spriteCenter)
{
	if (spriteCenter)
		return Vector2f(sprite.getPosition() + Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2));
	else 
		return Vector2f(body.getPosition() + body.getSize() / 2.f);
}
