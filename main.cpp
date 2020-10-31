#include  <SFML/Graphics.hpp>
#include <iostream>
#include "windows.h"

using namespace std;
using namespace sf;

//����� �������������� �� ����� ��������� (� ������� - �����������)
class Actor {
private:
	//������ ������
	RectangleShape hero;

	//����� ��� ������������
	bool leftPressed;
	bool rightPressed;
	bool upPressed;
	bool downPressed;

public:

	//����������� �������� ������������
	float speed = 0.5;

	Actor(Vector2f& size, Vector2f& position, Color& color) {
		hero.setSize(size);
		hero.setPosition(position);
		hero.setFillColor(color);
		leftPressed = false;
		rightPressed = false;
		upPressed = false;
		downPressed = false;
	}

	RectangleShape getHero() {
		return hero;
	}

	// ��� �������� 
	void moveLeft() {
		leftPressed = true;
	}

	void moveRight() {
		rightPressed = true;
	}

	void moveUp() {
		upPressed = true;
	}

	void moveDown() {
		downPressed = true;
	}

	// ����������� ��������
	void stopLeft() {
		leftPressed = false;
	}

	void stopRight() {
		rightPressed = false;
	}

	void stopUp() {
		upPressed = false;
	}

	void stopDown() {
		downPressed = false;
	}

	// (�� ������, ��� ��������� ��������� ������)
	//���������� ���������� � ����������� ��������
	Vector2f& getDirection() {
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

	//����� ��� ���������� ����� ��� ������ ��������� �������� �����
	//� ������ �������
	void update(float elapsedTime) {
		if (leftPressed)
			hero.move(-speed * elapsedTime, 0);

		if (rightPressed)
			hero.move(speed * elapsedTime, 0);

		if (upPressed)
			hero.move(0, -speed * elapsedTime);

		if (downPressed)
			hero.move(0, speed * elapsedTime);
	}

	//����� ��� ���������� ����� ��� ������ ��������� �������� �����
	//��� ����� �������
	void update() {
		if (leftPressed)
			hero.move(-speed, 0);

		if (rightPressed)
			hero.move(speed, 0);

		if (upPressed)
			hero.move(0, -speed);

		if (downPressed)
			hero.move(0, speed);
	}

	void shiftPosition(float x, float y) {
		hero.move(x, y);
	}
};

int main() {
	//������� ����
	RenderWindow window(VideoMode(500, 500), "maindo");
	//�������������� ������
	Vector2f heroSize(20, 30);
	Vector2f heroPosition(0, 0);
	Color color(255, 0, 0);
	//��������� �������������
	Actor activeActor(heroSize, heroPosition, color);

	RectangleShape mapBounds;
	mapBounds.setPosition(50, 50);
	mapBounds.setSize(Vector2f(400, 400));
	mapBounds.setFillColor(Color(255, 255, 255, 0));
	mapBounds.setOutlineThickness(4);
	mapBounds.setOutlineColor(Color(0, 255, 0));


	//����� ��� ��������
	Clock clock;
	//���������� ����������
	int i = 0;
	//������� ����
	while (window.isOpen()) {
		Event event;
		//����� ��� ��������
		float delta = clock.restart().asSeconds();
		
		//���������� ������� � ������� ������
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			//���������� ����������
			//cout << i++ << " " << event.type << " " << activeActor.getHero().getPosition().x << " " << activeActor.getHero().getPosition().y << endl;

			if (Keyboard::isKeyPressed(Keyboard::A))
				activeActor.moveLeft();

			if (event.type == Event::KeyReleased)
				if (event.key.code == Keyboard::A)
					activeActor.stopLeft();
			
			if (Keyboard::isKeyPressed(Keyboard::D))
				activeActor.moveRight();
			
			if (event.type == Event::KeyReleased)
				if (event.key.code == Keyboard::D)
					activeActor.stopRight();

			if (Keyboard::isKeyPressed(Keyboard::S))
				activeActor.moveDown();
			
			if (event.type == Event::KeyReleased)
				if (event.key.code == Keyboard::S)
					activeActor.stopDown();

			if (Keyboard::isKeyPressed(Keyboard::W))
				activeActor.moveUp();
			
			if (event.type == Event::KeyReleased)
				if (event.key.code == Keyboard::W)
					activeActor.stopUp();
		}
		
		//��������� ��������� ������������ ������
		activeActor.update();

		if (activeActor.getHero().getGlobalBounds().intersects(mapBounds.getGlobalBounds())) {
			//���������� ����������
			cout << mapBounds.getGlobalBounds().height << " " << mapBounds.getGlobalBounds().width << endl;
			//�����������, � ������� ���������� �������� ���������
			Vector2f forbiddenDirection = activeActor.getDirection();

			//cout << forbiddenDirection.x << " " << forbiddenDirection.y << endl;
			if (forbiddenDirection.x == 1) {
				activeActor.shiftPosition(-activeActor.speed, 0);
				activeActor.stopRight();
			}
			else if (forbiddenDirection.x == -1) {
				activeActor.shiftPosition(activeActor.speed, 0);
				activeActor.stopLeft();
			}
			if (forbiddenDirection.y == 1) {
				activeActor.shiftPosition(0, -activeActor.speed);
				activeActor.stopDown();
			}
			else if (forbiddenDirection.y == -1) {
				activeActor.shiftPosition(0, activeActor.speed);
				activeActor.stopUp();
			}
		}

		//������� ���������� ����
		window.clear();
		//������ ����� ��������� ������
		window.draw(mapBounds);
		window.draw(activeActor.getHero());
		
		//������������ ����� ��������� ������
		window.display();
		//���������� ����������
		i %= 100000;
	}
	return 0;
}