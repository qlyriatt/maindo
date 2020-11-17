#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


class gameObject 
{
public:
	bool allowCollision;
	short int interactableType;
private:
	Texture Texture;
	Sprite Sprite;
};