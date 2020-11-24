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
#define ESSENTIAL_OBJECTS 2

int main()
{
	cout << tan(-3.14 / 4) << " " << atan(1) << " " << atan(-1);
	int currentLvl = 0;
	int switchLvl = 1;

	Clock uni_clock;
	uni_clock.restart();
	RenderWindow window(VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "VeryGoodGame");
	srand(uni_clock.getElapsedTime().asSeconds());	//tmp

	//thats lvl pretty much
	vector<gameObject> objects;
	objects = initialize<gameObject>(1);

	// SPECIFY TEXTURE LOCATION
	Texture* playerTexture = new Texture;
	playerTexture->loadFromFile("D:/All mine/Game/player.png");
	Texture* bulletRifleTexture = new Texture;
	bulletRifleTexture->loadFromFile("D:/All mine/Game/bulletRifle.png");
	Texture* bulletPistolTexture = new Texture;
	bulletPistolTexture->loadFromFile("D:/All mine/Game/bulletPistol.png");

	// range, speed
	Weapon rifle(600, 400);
	rifle.projectileTexture = bulletRifleTexture;
	Weapon pistol(200, 200);
	pistol.projectileTexture = bulletPistolTexture;

	Player player(100, Vector2f(20, 20), playerTexture); //speed is pixels per second
	player.weapon = pistol;
	bool switchedWeapon = false;
	
	
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
				if (event.key.code == Keyboard::E)
				{
					interaction_flag = true;
				}
				if (event.key.code == Keyboard::Space)
				{
					projectiles.push_back(player.weapon.action(player.currentSight,player.getCenter(true) - Vector2f(0,5)));	//tmp
				}
				if (event.key.code == Keyboard::R)
				{
					if (switchedWeapon)
					{
						player.weapon = pistol;
						switchedWeapon = false;
					}
					else
					{
						player.weapon = rifle;
						switchedWeapon = true;
					}
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

		player.moving = player.upPressed or player.rightPressed or player.downPressed or player.leftPressed;
		
		player.updatePosition(uni_clock.getElapsedTime().asSeconds());

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
		player.collisionCheckInner(playerBounds);

		
		window.draw(objects.at(0).body);
		bool msg_displayed = false;
		for (int i = 1; i < objects.size(); i++)
		{
			bool coll = player.collisionCheck(objects.at(i), 1);
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
			coll = player.collisionCheck(interactionZone, 1);

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
					msg.setSize(Vector2f(20, 5));
					msg.setPosition(Vector2f(player.sprite.getPosition() + Vector2f(0, -10)));
					msg.setFillColor(Color(Color::White));
					window.draw(msg);
					msg_displayed = true;
				}
			}
			if (i == 2 and currentLvl == 0)
			{
				objects.at(i).script(0, Vector2f(400, 300), player.getCenter(), uni_clock.getElapsedTime().asSeconds());
			}
			window.draw(objects.at(i).body);
		}

		window.draw(player.sprite);

		for (int i = 0; i < projectiles.size(); i++)
		{
			bool was_erased = false;
			if (sqrt(projectiles.at(i).currentPosition.x * projectiles.at(i).currentPosition.x + projectiles.at(i).currentPosition.y * projectiles.at(i).currentPosition.y) < projectiles.at(i).range)
			{
				projectiles.at(i).updatePosition(uni_clock.getElapsedTime().asSeconds());
				for (int j = 1; j < objects.size(); j++)
				{
					if (projectiles.at(i).collisionCheck(objects.at(j), 1))
					{
						projectiles.erase(projectiles.begin() + i);
						i--;
						if (j > ESSENTIAL_OBJECTS)
						{
							objects.erase(objects.begin() + j);
						}
						was_erased = true;
						break;
					}
				}
				if (was_erased)
				{
					continue;
				}
				projectiles.at(i).currentPosition += projectiles.at(i).currentDirection * projectiles.at(i).latestDistanceCovered;
				window.draw(projectiles.at(i).sprite);
			}
			else
			{
				projectiles.erase(projectiles.begin() + i);
				i--;
			}


		}
		window.setView(minimap);

		
		for (int i = 0; i < objects.size(); i++)
		{
			window.draw(objects.at(i).body);
		}
		window.draw(player.sprite);
		for (int i = 0; i < projectiles.size(); i++)
		{
			window.draw(projectiles.at(i).sprite);
		}
		
		window.display();
		window.setView(camera);
	}

	return 0;
}


