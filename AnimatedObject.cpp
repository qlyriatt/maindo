#include "AnimatedObject.h";


//texture updates every 1/animationStates sec.
void AnimatedObject::updateAnimation(float elapsedTime)
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
