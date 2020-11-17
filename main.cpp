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

#define ESSENTIAL_OBJECTS 1

short int currentLvl = 0;
short int switchLvl = 1;

int main()
{
	RenderWindow window(VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "VeryGoodGame");

	//	ONLY RECTANGLE SHAPES
	vector<RectangleShape> objects;
	
	objects = initialize<RectangleShape>(1);

	RectangleShape outerBounds = objects.at(0);
	float outline = outerBounds.getOutlineThickness();
	FloatRect playerBounds(outerBounds.getPosition(), Vector2f(WINDOW_SIZE_X - 2 * outline, WINDOW_SIZE_Y - 2 * outline));
	Player player(20, 30, 20, 20, float(0.2));

	
	//some camera things
	View camera;
	camera.reset(FloatRect(0, 0, CAMERA_SIZE_X, CAMERA_SIZE_Y));
	camera.setViewport(FloatRect(0, 0, 1, 1));


	View minimap;
	minimap.reset(FloatRect(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y));
	minimap.setViewport(FloatRect(0.03, 0.75, 0.2, 0.2));



	while (window.isOpen())
	{
		if (currentLvl != switchLvl)
		{
			Clock clock;
			RectangleShape loadScreen;
			loadScreen.setSize(Vector2f(WINDOW_SIZE_X, WINDOW_SIZE_Y));
			loadScreen.setFillColor(Color(Color::Black));
			window.draw(loadScreen);
			window.display();

			objects.erase(objects.begin(), objects.end());
			objects = initialize<RectangleShape>(switchLvl);
			RectangleShape outerBounds = objects.at(0);
			float outline = outerBounds.getOutlineThickness();
			FloatRect playerBounds(outerBounds.getPosition(), Vector2f(WINDOW_SIZE_X - 2 * outline, WINDOW_SIZE_Y - 2 * outline));
			currentLvl = switchLvl;

			for (; floor(clock.getElapsedTime().asSeconds()) < 1;); //wait
			window.clear();
		}
		
		Event event;
			
		while (window.pollEvent(event)) 
		{
			if (event.type == Event::Closed)
				window.close();

			//FIX
			if (event.type == Event::LostFocus)
			{
				bool lostFocus = true;
				while (window.pollEvent(event) or lostFocus)
				{
					if (event.type == Event::GainedFocus)
						lostFocus = false;
				}
			}

			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					bool pause = true;
					RectangleShape pauseScreen;
					pauseScreen.setSize(Vector2f(WINDOW_SIZE_X, WINDOW_SIZE_Y));
					pauseScreen.setFillColor(Color(0, 0, 0, 150));
					window.draw(pauseScreen);

					vector<RectangleShape> pauseButtons;
					for (short int i = 0; i < 3; i++)
					{
						RectangleShape button;
						button.setSize(Vector2f(80, 10));
						button.setFillColor(Color(Color::White));
						button.setPosition(Vector2f(camera.getCenter().x - 40, camera.getCenter().y - 35 + 30 * i));
						pauseButtons.push_back(button);
						window.draw(button);
					}
					window.display();
					
					while (window.pollEvent(event) or pause)
					{
						if (event.type == Event::KeyPressed)
						{
							if (event.key.code == Keyboard::Escape)
								pause = false;
							else if (event.key.code == Keyboard::W)
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
				}
				else if (event.key.code == Keyboard::W)
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

		

		outerBounds.setOutlineColor(Color(255, 0, 0));
		outerBounds.setFillColor(Color(30, 19, 50));

		camera.setCenter(player.getbody().getPosition() + player.getbody().getSize() / 2.f);
		
		Vector2f topleft = camera.getCenter() - camera.getSize() / 2.f;
		Vector2f topright = topleft + Vector2f(camera.getSize().x, 0);
		Vector2f bottomleft = topleft + Vector2f(0, camera.getSize().y);
		Vector2f bottomright = camera.getCenter() + camera.getSize() / 2.f;
		bool TL = outerBounds.getGlobalBounds().contains(topleft);
		bool TR = outerBounds.getGlobalBounds().contains(topright);
		bool BL = outerBounds.getGlobalBounds().contains(bottomleft);
		bool BR = outerBounds.getGlobalBounds().contains(bottomright);

		//rect match (aka inner collision)
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

		player.collision_check_inner(playerBounds);
		window.draw(outerBounds);

		for (short unsigned int i = ESSENTIAL_OBJECTS; i < objects.size(); i++)
		{
			bool coll = player.collision_check(objects.at(i), player.getdirection());
			if (i == 1 and coll == true)
			{
				if (currentLvl == 0)
					switchLvl = 1;
				else if (currentLvl == 1)
					switchLvl = 0;
			}
			window.draw(objects.at(i));
		}

		window.draw(player.getbody());

		window.setView(minimap);
		outerBounds.setFillColor(Color(0, 0, 0, 150));
		outerBounds.setOutlineColor(Color(255, 0, 0, 150));
		window.draw(outerBounds);
		for (short unsigned int i = ESSENTIAL_OBJECTS; i < objects.size(); i++)
		{
			window.draw(objects.at(i));
		}
		window.draw(player.getbody());

		
		
		window.display();
		window.setView(camera);
	}

	return 0;
}


