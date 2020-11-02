#pragma once
#include  <SFML/Graphics.hpp>
#include <iostream>
#include "windows.h"
#include "Actor.h"
#include "Robot.h"

using namespace std;
using namespace sf;

class Kevin : public Actor {
private:
	Robot *robot;
	Weapon *kevinWeapons;

public:
	Kevin(Vector2f& size, Vector2f& position, Color& color);
};