#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Misc.h"
#include "Map.h"
#include "Player.h"

using namespace std;
using namespace sf;

#define WINDOW_SIZE_X 800
#define WINDOW_SIZE_Y 600
#define CAMERA_SIZE_X WINDOW_SIZE_X / 2
#define CAMERA_SIZE_Y WINDOW_SIZE_Y / 2
#define ESSENTIAL_OBJECTS 1

int currentLvl = 0;
int switchLvl = 1;


int main()
{
	RenderWindow window(VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "VeryGoodGame");
	//ONLY RECTANGLE SHAPES
	//vector<RectangleShape> objects;
	vector<gameObject> objects;
	
	objects = initialize<gameObject>(1);

	gameObject outerBounds = objects.at(0);
	float outline = outerBounds.body.getOutlineThickness();
	FloatRect playerBounds(outerBounds.body.getPosition(), Vector2f(WINDOW_SIZE_X - 2 * outline, WINDOW_SIZE_Y - 2 * outline));
	
	Texture *texture = new Texture;
	/////////////////////////////// SPECIFY TEXTURE LOCATION 
	if (!((*texture).loadFromFile("D:/All mine/Game/player.png")))
		return -1;
	Player player(0.2, Vector2f(20, 20), texture);
	player.weapon.range = 200;
	player.weapon.projectileSpeed = 0.5;
	//player.sprite.setTexture(texture);
	

	//some camera things
	View camera;
	camera.reset(FloatRect(0, 0, CAMERA_SIZE_X, CAMERA_SIZE_Y));
	camera.setViewport(FloatRect(0, 0, 1, 1));


	View minimap;
	minimap.reset(FloatRect(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y));
	minimap.setViewport(FloatRect(0.03, 0.75, 0.2, 0.2));



	while (window.isOpen())
	{
		bool interaction_flag = false;
		level_load(&window, &objects, &currentLvl, &switchLvl);
		
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
					pause(&window, &player, &camera);
				}
				else if (event.key.code == Keyboard::E)
					interaction_flag = true;
				else if (event.key.code == Keyboard::Space)
				{
					player.weapon.action(player.getSight(), &window, player.sprite.getPosition());
				}
				else
				{
					movement_handler(&event, &player, 1);
				}
			}

			if (event.type == Event::KeyReleased)
			{
				movement_handler(&event, &player, 0);
			}
		}
		window.clear();
		player.update(1);
		player.blink();

		

		outerBounds.body.setOutlineColor(Color(255, 0, 0));
		outerBounds.body.setFillColor(Color(30, 19, 50));

		camera.setCenter(player.getcenter(1));
		
		Vector2f topleft = camera.getCenter() - camera.getSize() / 2.f;
		Vector2f topright = topleft + Vector2f(camera.getSize().x, 0);
		Vector2f bottomleft = topleft + Vector2f(0, camera.getSize().y);
		Vector2f bottomright = camera.getCenter() + camera.getSize() / 2.f;
		bool TL = outerBounds.body.getGlobalBounds().contains(topleft);
		bool TR = outerBounds.body.getGlobalBounds().contains(topright);
		bool BL = outerBounds.body.getGlobalBounds().contains(bottomleft);
		bool BR = outerBounds.body.getGlobalBounds().contains(bottomright);

		//rect match (aka inner collision)
		if (!(TL and TR and BL and BR))
		{
			if (TL)
			{
				if (BL)
					camera.setCenter(Vector2f(WINDOW_SIZE_X - CAMERA_SIZE_X / 2, player.getcenter(1).y));
				else if (TR)
					camera.setCenter(Vector2f(player.getcenter(1).x, WINDOW_SIZE_Y - CAMERA_SIZE_Y / 2));
				else
					camera.setCenter(Vector2f(WINDOW_SIZE_X - CAMERA_SIZE_X / 2, WINDOW_SIZE_Y - CAMERA_SIZE_Y / 2));
			}

			else if (BR)
			{
				if (TR)
					camera.setCenter(Vector2f(CAMERA_SIZE_X / 2, player.getcenter(1).y));
				else if (BL)
					camera.setCenter(Vector2f(player.getcenter(1).x, CAMERA_SIZE_Y / 2));
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
		window.draw(outerBounds.body);

		bool msg_displayed = false;
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
			gameObject interactionZone;
			interactionZone.allowCollision = true;
			interactionZone.body.setSize(objects.at(i).body.getSize() + Vector2f(20, 20));
			interactionZone.body.setPosition(objects.at(i).body.getPosition() + Vector2f(-10, -10));
			coll = player.collision_check(interactionZone, player.getdirection());

			if (coll and !msg_displayed)
			{
				if (interaction_flag)
				{
					if (objects.at(i).body.getFillColor() == Color::Green)
						objects.at(i).body.setFillColor(Color(Color::Black));
					else
						objects.at(i).body.setFillColor(Color(Color::Green));
					interaction_flag = false;
				}
				else
				{
					RectangleShape msg;
					msg.setSize(Vector2f(30, 5));
					msg.setPosition(Vector2f(objects.at(i).body.getPosition() + Vector2f(-5, 30)));
					msg.setFillColor(Color(Color::White));
					window.draw(msg);
					msg_displayed = true;
				}
			}

			window.draw(objects.at(i).body);
		}

		window.draw(player.sprite);

		window.setView(minimap);
		outerBounds.body.setFillColor(Color(30, 19, 50, 150));
		outerBounds.body.setOutlineColor(Color(255, 0, 0, 150));
		window.draw(outerBounds.body);
		for (short unsigned int i = ESSENTIAL_OBJECTS; i < objects.size(); i++)
		{
			window.draw(objects.at(i).body);
		}
		window.draw(player.sprite);

		
		
		window.display();
		window.setView(camera);
	}

	return 0;
}


