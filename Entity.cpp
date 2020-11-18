#include "Entity.h"
#include <iostream>


Entity::Entity() :gameObject()
{
}

Entity::Entity(float speed, bool allowCollision, short int interactionType, Vector2f position, Vector2f size, Color color, float outline) :gameObject(speed, allowCollision, interactionType, position, size, color, outline)
{
}

Entity::Entity(float speed, Vector2f position, Texture texture) :gameObject(speed, position, texture)
{
}

