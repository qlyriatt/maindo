#pragma once
#include  <SFML/Graphics.hpp>
#include <iostream>
#include "windows.h"
#include "gameObject.h"
#include "Weapon.h"


using namespace std;
using namespace sf;

//����� �������������� �� ����� ��������� (� ������� - �����������)
class Actor {
private:
	//������ ������
	RectangleShape hero;

	string name;

	uint8_t healthPoints;

	Weapon *actorWeapons;

	//����� ��� ������������
	bool leftPressed;
	bool rightPressed;
	bool upPressed;
	bool downPressed;


public:

	//����������� �������� ������������
	float speed = 0.5;

	Actor(Vector2f& size, Vector2f& position, Color& color);

	RectangleShape getHero();

	// ��� �������� 
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	// ����������� ��������
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();

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