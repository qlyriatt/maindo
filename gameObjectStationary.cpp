#include "gameObjectStationary.h"


//basic
gameObjectStationary::gameObjectStationary(const Vector2f& position, const Texture& texture)
{
	sprite.setPosition(position);
	sprite.setTexture(texture);
	body.setPosition(position);
	body.setSize(Vector2f{ texture.getSize() });
}

//testing
gameObjectStationary::gameObjectStationary(const Vector2f& position, const Vector2f& size, 
	const int interactionType, const int interactionTypeSpeciality, const bool allowCollision)
{
	body.setPosition(position);
	body.setSize(size);
	body.setFillColor(Color(20, 20, 70));
	body.setOutlineColor(Color::Red);
	body.setOutlineThickness(4);

	this->interactionType = interactionType;
	this->interactionTypeSpeciality = interactionTypeSpeciality;
	this->allowCollision = allowCollision;
}

//final
gameObjectStationary::gameObjectStationary(const Vector2f& position, const Texture& texture, const size_t animationStates, const bool allowCollision, 
	const bool isDestroyable, const int interactionType, const int interactionTypeSpeciality, const float interactionRadius)
{
	sprite.setPosition(position);
	sprite.setTexture(texture);
	body.setPosition(position);
	body.setSize(Vector2f{ texture.getSize() });

	this->animationStates = animationStates;
	if (animationStates > 1)
		this->isAnimated = true;

	this->interactionType = interactionType;
	this->interactionTypeSpeciality = interactionTypeSpeciality;
	this->interactionRadius = interactionRadius;
	this->allowCollision = allowCollision;
	this->isDestroyable = isDestroyable;
}


Vector2f gameObjectStationary::getCenter() const
{
	return body.getPosition() + body.getSize() / 2.f;
}

//texture updates every 1/animationStates sec.
void gameObjectStationary::updateAnimation(const float elapsedTime)
{
	if (isAnimated)
	{
		const int x = int(animationCycleTimer * animationStates) % animationStates;

		IntRect textureRect({ int(body.getSize().x * x), 0 }, Vector2i{ body.getSize() });
		body.setTextureRect(textureRect);

		animationCycleTimer += elapsedTime - latestAnimationUpdate;
		latestAnimationUpdate = elapsedTime;
	}
}


