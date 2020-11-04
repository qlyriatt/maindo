#pragma once
#include  <SFML/Graphics.hpp>
#include <iostream>
//#include "windows.h"
//#include "gameObject.h"
//#include "Weapon.h"


using namespace std;
using namespace sf;

//����� �������������� �� ����� ��������� (� ������� - �����������)
class Entity {
protected:
	//������ ������
	RectangleShape body;
	
	//string name;

	//uint8_t healthPoints;

	//Weapon *Weapons;


public:
	
	Entity()
	{
		body.setSize(Vector2f(0, 0));
		body.setPosition(0, 0);
		basespeed = 0;
	};
	Entity(float, float, float, float, float);
	//Entity(Vector2f sizevector, float xpos, float ypos);

	//����������� �������� ������������
	float basespeed;
	float speed;
	//Entity(Vector2f& size, Vector2f& position, Color& color);

	RectangleShape getbody();
	// ��� �������� 
	//void setLeft();
	//void setRight();
	//void setUp();
	//void setDown();

	// ����������� ��������
	//void stopLeft();
	//void stopRight();
	//void stopUp();
	//void stopDown();

	// (�� ������, ��� ��������� ��������� ������)
	//���������� ���������� � ����������� ��������
	Vector2f& getDirection();

	//����� ��� ���������� ����� ��� ������ ��������� �������� �����
	//� ������ �������
	void update(float elapsedTime);

	//����� ��� ���������� ����� ��� ������ ��������� �������� �����
	//��� ����� �������
	void update();

	void shiftPosition(float x, float y);

	void fire();

	void interactive();

	void collisionCheck(RectangleShape *mapBounds, float *time);
};


Entity::Entity(float width, float height, float xpos, float ypos, float speed)
{
	Vector2f size(width, height);
	body.setSize(size);
	body.setPosition(xpos, ypos);
	this->basespeed = speed;
	this->speed = speed;
}

//Entity::Entity(Vector2f sizevector, float xpos, float ypos, float speed)
//{
//	body.setSize(sizevector);
//	body.setPosition(xpos, ypos);
//	this->speed = speed;
//}

RectangleShape Entity::getbody()
{
	return body;
}
