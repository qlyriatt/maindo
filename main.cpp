#include <SFML/Graphics.hpp>
#include <iostream>
#include "windows.h"
#include "Actor.h"
//#include "Kevin.h"
//#include "NPC.h"
//#include "Robot.h"
//#include "Weapon.h"
#include "Player.h"

using namespace std;
using namespace sf;



int main()
{
	RenderWindow window(VideoMode(800, 600), "Maindo");
	
	Player player(15, 30, 0, 0, 0.05);

	//��� ������ ����� ������ ��� �������
	//View alternativeView;
	//������������� ����� ������
	//alternativeView.setCenter(activeActor.getHero().getPosition());
	//������������� ������ ������� ���������� � ������
	//alternativeView.setSize(sf::Vector2f(1280, 720));
	//��� ������ 
	//alternativeView.zoom(4.f);
	//������������ ���� ������
	//alternativeView.setViewport(sf::FloatRect(0.25f, 0.25, 0.5f, 0.5f));

	RectangleShape mapBounds;
	mapBounds.setPosition(50, 50);
	mapBounds.setSize(Vector2f(400, 400));
	mapBounds.setFillColor(Color(255, 255, 255, 0));
	mapBounds.setOutlineThickness(4);
	mapBounds.setOutlineColor(Color(0, 255, 0));


	Clock clock;
	bool moving = 0;
	bool timef = 0;

	while (window.isOpen()) {
		Event event;
		
		if (timef)
		{
			clock.restart();
			timef = 0;
		}

		if ((moving == 1) and (player.speed <= 0.2))
		{
			player.speed = player.basespeed + 0.05 * clock.getElapsedTime().asSeconds();
			if (player.speed > 0.2)
				player.speed = 0.2;
			//cout << player.speed << "      " << clock.getElapsedTime().asSeconds() << endl;
		}



		while (window.pollEvent(event)) 
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)
			{
				moving = 1;
				if (event.key.code == Keyboard::W)
					player.upPressed = 1;
				else if (event.key.code == Keyboard::D)
					player.rightPressed = 1;
				else if (event.key.code == Keyboard::S)
					player.downPressed = 1;
				else if (event.key.code == Keyboard::A)
					player.leftPressed = 1;
			}

			if (event.type == Event::KeyReleased)
			{
				moving = false;
				player.speed = player.basespeed;
				timef = 1;

				if (event.key.code == Keyboard::W)
					player.upPressed = 0;
				else if (event.key.code == Keyboard::D)
					player.rightPressed = 0;
				else if (event.key.code == Keyboard::S)
					player.downPressed = 0;
				else if (event.key.code == Keyboard::A)
					player.leftPressed = 0;
			}
		}
		window.clear();

		player.update(1);

		//��������� ��������
		//activeActor.collisionCheck(&mapBounds, &time);

		//������� ���������� ����

		//������ ����� ������ ���, ����� ������ ������� �� �������
		//alternativeView.setCenter(activeActor.getHero().getPosition());
		//����������� ��������: ��������� ���� ��� �������
		//window.setView(alternativeView);

		//������ ����� ��������� ������
		window.draw(mapBounds);
		window.draw(player.getbody());
		
		//������������ ����� ��������� ������
		window.display();

	}

	return 0;
}