#pragma once
#include  <SFML/Graphics.hpp>
#include <iostream>
#include "windows.h"
#include "gameObject.h"
#include "Weapon.h"


using namespace std;
using namespace sf;

//класс передвигащихс€ по карте сущностей (в будущем - абстрактный)
class Actor {
private:
	//фигура актора
	RectangleShape hero;

	string name;

	uint8_t healthPoints;

	Weapon *actorWeapons;

	//флаги дл€ передвижени€
	bool leftPressed;
	bool rightPressed;
	bool upPressed;
	bool downPressed;


public:

	//коэффициент скорости передвижени€
	float speed = 0.5;

	Actor(Vector2f& size, Vector2f& position, Color& color);

	RectangleShape getHero();

	// ƒл€ движени€ 
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	// ѕрекращение движени€
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();

	// (не уверен, что правильно возвращаю ссылку)
	//возвращает информацию о направлении движени€
	Vector2f& getDirection();

	//метод дл€ обновлени€ полей дл€ каждой интерации игрового цикла
	//с учетом времени
	void update(float elapsedTime);

	//метод дл€ обновлени€ полей дл€ каждой интерации игрового цикла
	//без учета времени
	void update();

	void shiftPosition(float x, float y);

	void fire();

	void interactive();

	void collisionCheck(RectangleShape *mapBounds, float *time);
};