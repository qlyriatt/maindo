#pragma once
#include  <SFML/Graphics.hpp>
#include "gameObject.h"


class Entity : public gameObject
{	
public:
	Entity();
	Entity(float, Vector2f, Texture);
	Entity(float, bool, short int, Vector2f, Vector2f, Color, float);

};




