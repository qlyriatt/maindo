#include <SFML/Graphics.hpp>
#include <iostream>
#include "windows.h"
#include "Actor.h"
#include "Kevin.h"
#include "NPC.h"
#include "Robot.h"
#include "Weapon.h"

using namespace std;
using namespace sf;



int main() {
	//������� ����
	RenderWindow window(VideoMode(640, 310), "Maindo");
	//�������������� ������
	Vector2f heroSize(20, 30);
	Vector2f heroPosition(0, 0);
	Color color(255, 0, 0);
	//��������� �������������
	Kevin activeActor(heroSize, heroPosition, color);
	activeActor.speed = 100;
	//��� ������ ����� ������ ��� �������
	View alternativeView;
	//������������� ����� ������
	alternativeView.setCenter(activeActor.getHero().getPosition());
	//������������� ������ ������� ���������� � ������
	//alternativeView.setSize(sf::Vector2f(1280, 720));
	//��� ������ 
	//alternativeView.zoom(4.f);
	//������������ ���� ������
	alternativeView.setViewport(sf::FloatRect(0.25f, 0.25, 0.5f, 0.5f));

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
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();

		
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
		activeActor.update(time);

		//��������� ��������
		activeActor.collisionCheck(&mapBounds, &time);

		//������� ���������� ����
		window.clear();

		//������ ����� ������ ���, ����� ������ ������� �� �������
		alternativeView.setCenter(activeActor.getHero().getPosition());
		//����������� ��������: ��������� ���� ��� �������
		//window.setView(alternativeView);

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