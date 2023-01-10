#include "BasicObject.h"

void BasicObject::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	sprite.getTexture() ? target.draw(sprite) : target.draw(body);
}

inline bool BasicObject::collisionCheck(const FloatRect &obstacle) const
{
	if (body.getGlobalBounds().intersects(obstacle))
		return true;
	return false;
}


bool BasicObject::collisionCheck(const RectangleShape& obstacle) const
{
	if (collisionCheck(obstacle.getGlobalBounds()))
		return true;
	return false;
}


bool BasicObject::collisionCheck(const BasicObject& obstacle) const
{	
	if (collisionCheck(obstacle.body.getGlobalBounds()))
		return true;
	return false;
}


//texture updates every 1/animationStates sec.
void BasicObject::updateAnimation(float elapsedTime)
{
	if (isAnimated)
	{
		const int x = int(animationCycleTimer * animationStates) % animationStates;

		sf::IntRect textureRect({ int(body.getSize().x * x), 0 }, sf::Vector2i{ body.getSize() });
		body.setTextureRect(textureRect);

		animationCycleTimer += elapsedTime - latestAnimationUpdateTime;
		latestAnimationUpdateTime = elapsedTime;
	}
}
