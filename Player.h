#pragma once
#include "Actor.h"
#include "Weapon.h"
#include <iostream>

using namespace std;

class Player : public Entity
{
public:

	Player() : Entity() {};
	Player(float,float,float,float,float);
	
	//флаги для передвижения
	bool upPressed = 0;
	bool rightPressed = 0;
	bool downPressed = 0;
	bool leftPressed = 0;
	
	void update();
	void update(int);

private:
};

Player::Player(float xsize, float ysize, float xpos, float ypos, float speed) :Entity(xsize, ysize, xpos, ypos, speed)
{
};

void Player::update()
{
	if (upPressed)
		body.move(0, -basespeed);
	if (rightPressed)
		body.move(basespeed, 0);
	if (downPressed)
		body.move(0,basespeed);
	if (leftPressed)
		body.move(-basespeed, 0);
}

void Player::update(int)
{
	if (upPressed)
		body.move(0, -speed);
	if (rightPressed)
		body.move(speed, 0);
	if (downPressed)
		body.move(0, speed);
	if (leftPressed)
		body.move(-speed, 0);
}