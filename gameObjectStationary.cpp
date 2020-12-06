#include "gameObjectStationary.h"

gameObjectStationary::~gameObjectStationary() {};

gameObjectStationary::gameObjectStationary()
{
	animated = allowCollision = isDestroyable = false;
	animationCycleTimer = latestAnimationUpdate = interactionRadius = interactionType = 0;
}

gameObjectStationary::gameObjectStationary(Vector2f position, Vector2f size, Texture* texture, bool allowCollision,
	Color bodyColor, Color outlineColor, float outlineThickness)
{
	body.setPosition(position);

	body.setSize(size);

	body.setTexture(texture);

	this->allowCollision = allowCollision;

	animated = interactionType = isDestroyable = false;
	animationCycleTimer = latestAnimationUpdate = interactionRadius = interactionType = 0;



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
	if (animated)
	{
		int x = int(floor(animationCycleTimer * animationCycles)) % animationCycles; 

		IntRect neededTextureRect(Vector2i(body.getSize().x * x, 0), Vector2i(body.getSize()));
		body.setTextureRect(neededTextureRect);

		animationCycleTimer += elapsedTime - latestAnimationUpdate;
		latestAnimationUpdate = elapsedTime;
	}
}


