#include  <SFML/Graphics.hpp>
#include <iostream>
#include "windows.h"
#include "Actor.h"
#include "gameObject.h"



using namespace std;
using namespace sf;

	Actor::Actor(Vector2f& size, Vector2f& position, Color& color) {
		hero.setSize(size);
		hero.setPosition(position);
		hero.setFillColor(color);
		leftPressed = false;
		rightPressed = false;
		upPressed = false;
		downPressed = false;
	}

	RectangleShape Actor::getHero() {
		return hero;
	}

	// Для движения 
	void Actor::moveLeft() {
		leftPressed = true;
	}

	void Actor::moveRight() {
		rightPressed = true;
	}

	void Actor::moveUp() {
		upPressed = true;
	}

	void Actor::moveDown() {
		downPressed = true;
	}

	// Прекращение движения
	void Actor::stopLeft() {
		leftPressed = false;
	}

	void Actor::stopRight() {
		rightPressed = false;
	}

	void Actor::stopUp() {
		upPressed = false;
	}

	void Actor::stopDown() {
		downPressed = false;
	}

	// (не уверен, что правильно возвращаю ссылку)
	//возвращает информацию о направлении движения
	Vector2f& Actor::getDirection() {
		float x, y;
		if (leftPressed)
			x = -1;
		else if (rightPressed)
			x = 1;
		else
			x = 0;

		if (upPressed)
			y = -1;
		else if (downPressed)
			y = 1;
		else
			y = 0;

		Vector2f direction(x, y);

		return direction;
	}

	//метод для обновления полей для каждой интерации игрового цикла
	//с учетом времени
	void Actor::update(float elapsedTime) {
		if (leftPressed)
			hero.move(-speed * elapsedTime, 0);

		if (rightPressed)
			hero.move(speed * elapsedTime, 0);

		if (upPressed)
			hero.move(0, -speed * elapsedTime);

		if (downPressed)
			hero.move(0, speed * elapsedTime);
	}

	//метод для обновления полей для каждой интерации игрового цикла
	//без учета времени
	void Actor::update() {
		if (leftPressed)
			hero.move(-speed, 0);

		if (rightPressed)
			hero.move(speed, 0);

		if (upPressed)
			hero.move(0, -speed);

		if (downPressed)
			hero.move(0, speed);
	}

	void Actor::shiftPosition(float x, float y) {
		hero.move(x, y);
	}

	void Actor::collisionCheck(RectangleShape *mapBounds, float *time) {
		if (this->getHero().getGlobalBounds().intersects(mapBounds->getGlobalBounds())) {
			//отладочная информация
			//cout << mapBounds.getGlobalBounds().height << " " << mapBounds.getGlobalBounds().width << endl;

			//направление, в котором дальнейшее движение запрещено
			Vector2f forbiddenDirection = this->getDirection();

			//cout << forbiddenDirection.x << " " << forbiddenDirection.y << endl;
			if (forbiddenDirection.x == 1) {
				this->shiftPosition(-this->speed * (*time), 0);
				this->stopRight();
			}
			else if (forbiddenDirection.x == -1) {
				this->shiftPosition(this->speed * (*time), 0);
				this->stopLeft();
			}
			if (forbiddenDirection.y == 1) {
				this->shiftPosition(0, -this->speed * (*time));
				this->stopDown();
			}
			else if (forbiddenDirection.y == -1) {
				this->shiftPosition(0, this->speed * (*time));
				this->stopUp();
			}
		}
	}
