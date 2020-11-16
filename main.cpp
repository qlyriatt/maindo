#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Player.h"
#include "Entity.h"


using namespace std;
using namespace sf;

#define WINDOW_SIZE_X 800
#define WINDOW_SIZE_Y 600
#define CAMERA_SIZE_X WINDOW_SIZE_X / 2
#define CAMERA_SIZE_Y WINDOW_SIZE_Y / 2

#define ESSENTIAL_OBJECTS 2



int main()
{
	RenderWindow window(VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "VeryGoodGame");

	//	ONLY RECTANGLE SHAPES
	vector<RectangleShape> objects;
	
	objects = initialize<RectangleShape>(1);

	RectangleShape outerBounds = objects.at(0);
	RectangleShape mapBounds = objects.at(1);

	float outline = outerBounds.getOutlineThickness();
	
	FloatRect playerBounds(outerBounds.getPosition(), Vector2f(WINDOW_SIZE_X - 2 * outline, WINDOW_SIZE_Y - 2 * outline));

	Player player(20, 30, 20, 20, float(0.15));


	while (window.isOpen())
	{
		Event event;
			
		while (window.pollEvent(event)) 
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::LostFocus)
				player.upPressed = player.rightPressed = player.downPressed = player.leftPressed = false;

			//pressed keys
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::W)
					player.upPressed = 1;
				else if (event.key.code == Keyboard::D)
					player.rightPressed = 1;
				else if (event.key.code == Keyboard::S)
					player.downPressed = 1;
				else if (event.key.code == Keyboard::A)
					player.leftPressed = 1;
				else if (event.key.code == Keyboard::LShift)
				{
					player.leftShiftPressed = 1;
					player.setspeed(player.getbasespeed() / 2);
				}
			}

			//released keys
			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::W)
					player.upPressed = 0;
				else if (event.key.code == Keyboard::D)
					player.rightPressed = 0;
				else if (event.key.code == Keyboard::S)
					player.downPressed = 0;
				else if (event.key.code == Keyboard::A)
					player.leftPressed = 0;
				else if (event.key.code == Keyboard::LShift)
				{
					player.leftShiftPressed = 0;
					player.setspeed(player.getbasespeed());
				}
			}
		}


		window.clear();
		player.update(1);
		player.blink();

		

		//some camera things

		View camera;
		FloatRect camerabounds(0, 0, CAMERA_SIZE_X, CAMERA_SIZE_Y);
		camera.reset(camerabounds);
		camera.setViewport(FloatRect(0, 0, 1, 1));


		camera.reset(camerabounds);
		camera.setViewport(FloatRect(0, 0, 1, 1));
		camera.setCenter(player.getbody().getPosition() + player.getbody().getSize() / 2.f);
		outerBounds.setOutlineColor(Color(255, 0, 0));
		outerBounds.setFillColor(Color(30, 19, 50));


		Vector2f topleft = camera.getCenter() - camera.getSize() / 2.f;
		Vector2f topright = topleft + Vector2f(camera.getSize().x, 0);
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

		player.collision_check(mapBounds, player.getdirection());

		player.collision_check_inner(playerBounds);


		window.draw(outerBounds);
		window.draw(mapBounds);

		for (short int i = ESSENTIAL_OBJECTS; i < objects.size(); i++)
		{
			player.collision_check(objects.at(i), player.getdirection());
			window.draw(objects.at(i));
		}

		window.draw(player.getbody());




		camera.reset(FloatRect(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y));
		camera.setViewport(FloatRect(0.03, 0.75, 0.2, 0.2));
		window.setView(camera);
		outerBounds.setFillColor(Color(0, 0, 0, 150));
		outerBounds.setOutlineColor(Color(255, 0, 0, 150));
		window.draw(outerBounds);
		window.draw(mapBounds);

		for (short int i = ESSENTIAL_OBJECTS; i < objects.size(); i++)
		{
			window.draw(objects.at(i));
		}
		window.draw(player.getbody());

		window.display();

	}

	return 0;
}


