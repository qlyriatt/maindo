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
	float speed = 1;

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
};

int main() {
	//������� ����
	RenderWindow window(VideoMode(500, 500), "maindo");
	//�������������� ������
	Vector2f heroSize(20, 30);
	Vector2f heroPosition(10, 20);
	Color color(255, 0, 0);
	//��������� �������������
	Actor activeActor(heroSize, heroPosition, color);
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
			cout << i++ << " " << event.type << " " << activeActor.getHero().getPosition().x << " " << activeActor.getHero().getPosition().y << endl;

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
		//������� ���������� ����
		window.clear();
		//������ ����� ��������� ������
		window.draw(activeActor.getHero());
		//������������ ����� ��������� ������
		window.display();
		//���������� ����������
		i %= 100000;
	}
	return 0;
}