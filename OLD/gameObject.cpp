#include "gameObject.h"


// //minimal
// gameObject::gameObject(const Vector2f& position, const Texture& texture) : gameObjectStationary(position, texture) {}

// //testing
// gameObject::gameObject(const Vector2f& position, const Vector2f& size, const float basespeed, 
// 	const int interactionType, const int interactionTypeSpeciality, const bool allowCollision) : 
// 	gameObjectStationary(position, size, interactionType, interactionTypeSpeciality, allowCollision)
// {
// 	this->speed = this->basespeed = basespeed;
// }

// //final
// gameObject::gameObject(const Vector2f& position, const Texture& texture, const size_t animationStates, const float basespeed, 
// 	const bool allowCollision, const bool isDestroyable, const int interactionType, const int interactionTypeSpeciality, const size_t interactionRadius) :
// 	gameObjectStationary(position, texture, animationStates, allowCollision, isDestroyable, interactionType, interactionTypeSpeciality, interactionRadius)
// {
// 	this->speed = this->basespeed = basespeed;
// }




// void gameObject::collisionCheckInner(const FloatRect& area)
// {
// 	bool TL = area.contains(body.getPosition());
// 	bool TR = area.contains(body.getPosition() + Vector2f(body.getGlobalBounds().width, 0));
// 	bool BL = area.contains(body.getPosition() + Vector2f(0, body.getGlobalBounds().height));
// 	bool BR = area.contains(body.getPosition() + Vector2f(body.getGlobalBounds().width,body.getGlobalBounds().height));

// 	if (!(TL and TR and BR and BL))
// 		body.move(-currentDirection * latestDistanceCovered);
// }


