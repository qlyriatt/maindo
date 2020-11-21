#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "gameObject.h"
#include "Misc.h"
#include "Map.h"
#include "Player.h"
#include "Weapon.h"

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
	
	//thats lvl pretty much
	vector<gameObject> objects;
	objects = initialize<gameObject>(1);

	
	Texture *texture = new Texture;
	//////////SPECIFY TEXTURE LOCATION 
	//if (!((*texture).loadFromFile(               )))
		//return -1;

	Player player(0.2, Vector2f(20, 20), texture);
	player.weapon.range = 200;
	player.weapon.projectileSpeed = 0.5;
	

	//some camera things
	View camera;
	camera.reset(FloatRect(0, 0, CAMERA_SIZE_X, CAMERA_SIZE_Y));
	camera.setViewport(FloatRect(0, 0, 1, 1));

	View minimap;
	minimap.reset(FloatRect(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y));
	minimap.setViewport(FloatRect(0.03, 0.75, 0.2, 0.2));

	vector<Projectile> projectiles;

	level_load(&window, &objects, &currentLvl, &switchLvl);

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
				{
					interaction_flag = true;
				}
				else if (event.key.code == Keyboard::Space)
				{
					projectiles.push_back(player.weapon.action(player.getSight(),player.sprite.getPosition()));
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

		//constructing playground
		float outline = objects.at(0).body.getOutlineThickness();
		FloatRect playerBounds(objects.at(0).body.getPosition(), Vector2f(WINDOW_SIZE_X - 2 * outline, WINDOW_SIZE_Y - 2 * outline));

		window.clear();
		player.update();


		FloatRect outerBounds = objects.at(0).body.getGlobalBounds();
		camera.setCenter(player.getCenter(1));
		Vector2f topleft = camera.getCenter() - camera.getSize() / 2.f;
		Vector2f topright = topleft + Vector2f(camera.getSize().x, 0);
		Vector2f bottomleft = topleft + Vector2f(0, camera.getSize().y);
		Vector2f bottomright = camera.getCenter() + camera.getSize() / 2.f;

		bool TL = outerBounds.contains(topleft);
		bool TR = outerBounds.contains(topright);
		bool BL = outerBounds.contains(bottomleft);
		bool BR = outerBounds.contains(bottomright);

		//rect match (aka inner collision)
		if (!(TL and TR and BL and BR))
		{
			if (TL)
			{
				if (BL)
					camera.setCenter(Vector2f(WINDOW_SIZE_X - CAMERA_SIZE_X / 2, player.getCenter(1).y));
				else if (TR)
					camera.setCenter(Vector2f(player.getCenter(1).x, WINDOW_SIZE_Y - CAMERA_SIZE_Y / 2));
				else
					camera.setCenter(Vector2f(WINDOW_SIZE_X - CAMERA_SIZE_X / 2, WINDOW_SIZE_Y - CAMERA_SIZE_Y / 2));
			}

			else if (BR)
			{
				if (TR)
					camera.setCenter(Vector2f(CAMERA_SIZE_X / 2, player.getCenter(1).y));
				else if (BL)
					camera.setCenter(Vector2f(player.getCenter(1).x, CAMERA_SIZE_Y / 2));
				else
					camera.setCenter(Vector2f(CAMERA_SIZE_X / 2, CAMERA_SIZE_Y / 2));
			}

			else if (BL)
				camera.setCenter(Vector2f(WINDOW_SIZE_X - CAMERA_SIZE_X / 2, CAMERA_SIZE_Y / 2));
			else if (TR)
				camera.setCenter(Vector2f(CAMERA_SIZE_X / 2, WINDOW_SIZE_Y - CAMERA_SIZE_Y / 2));
		}
		player.collision_check_inner(playerBounds);

		
		window.draw(objects.at(0).body);
		bool msg_displayed = false;
		for (int i = 1; i < objects.size(); i++)
		{
			bool coll = player.collision_check(objects.at(i), player.getDirection());
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
			coll = player.collision_check(interactionZone, player.getDirection());

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

		for (int i = 0, erased = 0; i < projectiles.size(); i++)
		{
			if (sqrt(projectiles.at(i - erased).currentPosition.x * projectiles.at(i - erased).currentPosition.x + projectiles.at(i - erased).currentPosition.y * projectiles.at(i - erased).currentPosition.y) < projectiles.at(i - erased).range)
			{
				projectiles.at(i - erased).projectile.body.move(projectiles.at(i - erased).shotDirection * projectiles.at(i - erased).projectile.speed);
				projectiles.at(i - erased).currentPosition += projectiles.at(i - erased).shotDirection * projectiles.at(i - erased).projectile.speed;
				window.draw(projectiles.at(i - erased).projectile.body);
			}
			else
			{
				projectiles.erase(projectiles.begin() + i - erased);
				cout << projectiles.size() << endl; 
				i--;
			}
		}

		window.setView(minimap);

		//outerBounds.body.setFillColor(Color(30, 19, 50, 150));
		//outerBounds.body.setOutlineColor(Color(255, 0, 0, 150));
		//window.draw(outerBounds.body);

		for (int i = 0; i < objects.size(); i++)
		{
			window.draw(objects.at(i).body);
		}
		window.draw(player.sprite);

		for (int i = 0; i < projectiles.size(); i++)
		{
			window.draw(projectiles.at(i).projectile.body);
		}
		
		window.display();
		window.setView(camera);
	}

	return 0;
}


