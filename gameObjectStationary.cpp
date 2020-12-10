#include "gameObjectStationary.h"

gameObjectStationary::~gameObjectStationary() {};

gameObjectStationary::gameObjectStationary()
{
	isAnimated = allowCollision = isDestroyable = false;
	animationCycleTimer = latestAnimationUpdate = interactionRadius = interactionType = interactionTypeSpeciality = 0;
}

gameObjectStationary::gameObjectStationary(Vector2f position, Vector2f size, Texture* texture, bool allowCollision,
	Color bodyColor, Color outlineColor, float outlineThickness)
{
	isAnimated = interactionType = isDestroyable = false;
	animationCycleTimer = latestAnimationUpdate = interactionType = interactionTypeSpeciality = 0;

	body.setPosition(position);
	body.setSize(size);
	body.setTexture(texture);

	this->allowCollision = allowCollision;
	interactionRadius = 10;

	//to be removed
	body.setFillColor(bodyColor);
	body.setOutlineColor(outlineColor);
	body.setOutlineThickness(outlineThickness);
}

Vector2f gameObjectStationary::getCenter()
{
	return Vector2f(body.getPosition() + body.getSize() / 2.f);
}

//texture updates every 1/animationCycles sec.
void gameObjectStationary::updateAnimation(float elapsedTime, const Texture* texture, int animationCycles)
{
	if (isAnimated)
	{
		int x = int(floor(animationCycleTimer * animationCycles)) % animationCycles; 

		IntRect neededTextureRect(Vector2i(body.getSize().x * x, 0), Vector2i(body.getSize()));
		body.setTextureRect(neededTextureRect);

		animationCycleTimer += elapsedTime - latestAnimationUpdate;
		latestAnimationUpdate = elapsedTime;
	}
}


