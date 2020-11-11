#include <SFML/Graphics.hpp>
#include <iostream>
#include "windows.h"
#include "Entity.h"
//#include "Kevin.h"
//#include "NPC.h"
//#include "Robot.h"
//#include "Weapon.h"
#include "Player.h"

using namespace std;
using namespace sf;

#define WINDOW_SIZE_X 800
#define WINDOW_SIZE_Y 600
#define CAMERA_SIZE_X WINDOW_SIZE_X / 2
#define CAMERA_SIZE_Y WINDOW_SIZE_Y / 2


int main()
{
	RenderWindow window(VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Maindo");
	
	Player player(20, 30, 190, 135, float(0.15));


	RectangleShape outerBounds;
	float outline = 4;
	outerBounds.setSize(Vector2f(WINDOW_SIZE_X - 2 * outline, WINDOW_SIZE_Y - 2 * outline));
	outerBounds.setPosition(Vector2f(outline, outline));
	outerBounds.setOutlineThickness(outline);
	outerBounds.setOutlineColor(Color(255, 0, 0));
	outerBounds.setFillColor(Color(255, 255, 255,0));

	FloatRect playerBounds(Vector2f(outline, outline), Vector2f(WINDOW_SIZE_X - 2 * outline, WINDOW_SIZE_Y - 2 * outline));


	RectangleShape mapBounds;
	mapBounds.setPosition(200, 200);
	mapBounds.setSize(Vector2f(400, 200));
	mapBounds.setOutlineThickness(4);
	mapBounds.setFillColor(Color(50, 20, 20));
	mapBounds.setOutlineColor(Color(255, 0, 0));

	
	//Clock clock;
	//bool moving = 0;
	//bool timef = 0;
	
	bool moving = false;

	View camera;
	FloatRect camerabounds(0, 0, CAMERA_SIZE_X, CAMERA_SIZE_Y);
	camera.reset(camerabounds);
	camera.setViewport(FloatRect(0,0,1,1));


	while (window.isOpen()) {
		Event event;
		
		//if (timef)
		//{
		//	clock.restart();
		//	timef = 0;
		//}

		//if ((moving == 1) and (player.getspeed() <= 0.2))
		//{
		//	player.setspeed(player.getbasespeed() + 0.05 * clock.getElapsedTime().asSeconds());
		//	if (player.getspeed() > 0.2)
		//		player.setspeed(0.2);
		//}



		while (window.pollEvent(event)) 
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::LostFocus)
				player.upPressed = player.rightPressed = player.downPressed = player.leftPressed = false;

			if (event.type == Event::KeyPressed)
			{
				moving = true;
				if (event.key.code == Keyboard::W)
					player.upPressed = 1;
				else if (event.key.code == Keyboard::D)
					player.rightPressed = 1;
				else if (event.key.code == Keyboard::S)
					player.downPressed = 1;
				else if (event.key.code == Keyboard::A)
					player.leftPressed = 1;
				else if (event.key.code == Keyboard::LShift)
					player.setspeed(player.getbasespeed() / 2);
			}

			if (event.type == Event::KeyReleased)
			{
				moving = false;
				//player.setspeed(player.getbasespeed());
				//timef = 1;

				if (event.key.code == Keyboard::W)
					player.upPressed = 0;
				else if (event.key.code == Keyboard::D)
					player.rightPressed = 0;
				else if (event.key.code == Keyboard::S)
					player.downPressed = 0;
				else if (event.key.code == Keyboard::A)
					player.leftPressed = 0;
				else if (event.key.code == Keyboard::LShift)
					player.setspeed(player.getbasespeed());
			}
		}

		window.clear();
		player.update(1);
		//if (mapBounds.getGlobalBounds().contains(player.getbody().getPosition() + player.getbody().getPoint(0)))
		player.collision_check(mapBounds);

		player.collision_check_inner(playerBounds);








		camera.reset(camerabounds);
		camera.setViewport(FloatRect(0, 0, 1, 1));
		camera.setCenter(player.getbody().getPosition() + player.getbody().getSize() / 2.f);
		outerBounds.setOutlineColor(Color(255, 0, 0));
		outerBounds.setFillColor(Color(30, 19, 50));


		Vector2f topleft = camera.getCenter() - camera.getSize() / 2.f;
		Vector2f topright = topleft + Vector2f(camera.getSize().x,0);
		Vector2f bottomleft = topleft + Vector2f(0, camera.getSize().y);
		Vector2f bottomright = camera.getCenter() + camera.getSize() / 2.f;
		
		bool TL = outerBounds.getGlobalBounds().contains(topleft);
		bool TR = outerBounds.getGlobalBounds().contains(topright);
		bool BL = outerBounds.getGlobalBounds().contains(bottomleft);
		bool BR = outerBounds.getGlobalBounds().contains(bottomright);

		//rect match
		if (!(TL and TR and BL and BR))
		{
			if (TL)
			{
				if (BL)
					camera.setCenter(Vector2f(WINDOW_SIZE_X - CAMERA_SIZE_X / 2, player.getcenter().y));
				else if (TR)
					camera.setCenter(Vector2f(player.getcenter().x, WINDOW_SIZE_Y - CAMERA_SIZE_Y / 2));
				else
					camera.setCenter(Vector2f(WINDOW_SIZE_X - CAMERA_SIZE_X / 2, WINDOW_SIZE_Y - CAMERA_SIZE_Y / 2));
			}

			else if (BR)
			{
				if (TR)
					camera.setCenter(Vector2f(CAMERA_SIZE_X / 2, player.getcenter().y));
				else if (BL)
					camera.setCenter(Vector2f(player.getcenter().x, CAMERA_SIZE_Y / 2));
				else
					camera.setCenter(Vector2f(CAMERA_SIZE_X / 2, CAMERA_SIZE_Y / 2));
			}

			else if (BL)
				camera.setCenter(Vector2f(WINDOW_SIZE_X - CAMERA_SIZE_X / 2, CAMERA_SIZE_Y / 2));
			else if (TR)
				camera.setCenter(Vector2f(CAMERA_SIZE_X / 2, WINDOW_SIZE_Y - CAMERA_SIZE_Y / 2));
		}

		
		window.setView(camera);
		window.draw(outerBounds);
		window.draw(mapBounds);
		window.draw(player.getbody());

		camera.reset(FloatRect(0, 0, 800, 600));
		camera.setViewport(FloatRect(0.03, 0.75, 0.2, 0.2));
		window.setView(camera);
		outerBounds.setFillColor(Color(0, 0, 0, 150));
		outerBounds.setOutlineColor(Color(255, 0, 0, 150));
		window.draw(outerBounds);
		window.draw(mapBounds);
		window.draw(player.getbody());
		
		window.display();

	}

	return 0;
}


