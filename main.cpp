#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "gameObject.h"
#include "Misc.h"
#include "Map.h"
#include "Player.h"
#include "Weapon.h"
#include "Entity.h"

using namespace std;
using namespace sf;

const Vector2f WINDOW_SIZE = Vector2f(800, 600);
const Vector2f CAMERA_SIZE = Vector2f(400, 300);
#define ESSENTIALS 2

// INPUT --> PROJECTILE --> POSITION --> COLLISION CHECK --> CAMERA --> DRAW
//	 ^													|
//   |------------------INPUT OVERRIDE-------------------


int main()
{
	RenderWindow window(VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), pickName());
	
	View camera;
	camera.reset(FloatRect(Vector2f(0, 0), CAMERA_SIZE));
	camera.setViewport(FloatRect(0, 0, 1, 1));
	View minimap;
	minimap.reset(FloatRect(Vector2f(0, 0), WINDOW_SIZE));
	minimap.setViewport(FloatRect(0.35, 0.7, 0.3, 0.3)); //0.03, 0.75, 0.2, 0.2

	vector<Texture*> textures;

	Texture* playerTexture = new Texture;
	playerTexture->loadFromFile("D:/All mine/Game/player.png");
	Texture* bulletRifleTexture = new Texture;
	bulletRifleTexture->loadFromFile("D:/All mine/Game/bulletRifle.png");
	textures.push_back(bulletRifleTexture);
	Texture* bulletPistolTexture = new Texture;
	bulletPistolTexture->loadFromFile("D:/All mine/Game/bulletPistol.png");
	textures.push_back(bulletPistolTexture);

	Weapon rifle(600, 400, NULL, bulletRifleTexture, 5);
	Weapon pistol(200, 200, NULL, bulletPistolTexture, 3);

	Player player(Vector2f(20, 20), Vector2f(20, 30), playerTexture, 200); //speed is pixels per second
	player.weapon = pistol;
	bool switchedWeapon = false;
	
	vector<gameObject> objects;
	vector<Projectile> projectiles;
	vector<Entity> entities;


	int currentLevel = 1;
	levelLoad(&window, &objects, &entities, &currentLevel, 1, &textures);
	Clock uni_clock;

	while (window.isOpen())
	{
		bool interactionFlag = false;
		Event event;
		//---INPUT PHASE
		while (window.pollEvent(event)) 
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					pause(&window, &player, &camera);
				}
				if (event.key.code == Keyboard::E)
				{
					interactionFlag = true;
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
			}
		}
		window.clear();

		if (Keyboard::isKeyPressed(Keyboard::W))
			player.upPressed = true;
		else
			player.upPressed = false;
		if (Keyboard::isKeyPressed(Keyboard::D))
			player.rightPressed = true;
		else
			player.rightPressed = false;
		if (Keyboard::isKeyPressed(Keyboard::S))
			player.downPressed = true;
		else
			player.downPressed = false;
		if (Keyboard::isKeyPressed(Keyboard::A))
			player.leftPressed = true;
		else
			player.leftPressed = false;
		if (Keyboard::isKeyPressed(Keyboard::LShift))
			player.leftShiftPressed = true;
		else
			player.leftShiftPressed = false;
		if (Keyboard::isKeyPressed(Keyboard::Space))
			player.weapon.action(player.currentSight, player.getCenter() - Vector2f(0, 5), uni_clock.getElapsedTime().asSeconds(), &projectiles);
		//---INPUT PHASE END

		//---PROJECTILE PHASE
		for (size_t i = 0; i < projectiles.size(); i++)
		{
			bool projectileErased = false;
			float traveledDistance = sqrt(pow(projectiles.at(i).currentPosition.x, 2) + pow(projectiles.at(i).currentPosition.y, 2)); //x^2 + y^2

			if (traveledDistance < projectiles.at(i).range)
			{
				projectiles.at(i).updatePosition(uni_clock.getElapsedTime().asSeconds());

				for (size_t j = 1; j < objects.size(); j++)
				{
					if (projectiles.at(i).collisionCheck(objects.at(j)))
					{
						if (objects.at(j).destroyable)
						{
							objects.erase(objects.begin() + j);
							j--;
							if (projectiles.at(i).penetration)
							{
								projectiles.at(i).penetration--;
								continue;
							}
						}

						projectiles.erase(projectiles.begin() + i);
						i--;
						projectileErased = true;
						break;
					}
				}
				
				if(!projectileErased)
					projectiles.at(i).currentPosition += projectiles.at(i).currentDirection * projectiles.at(i).latestDistanceCovered;
			}
			else
			{
				projectiles.erase(projectiles.begin() + i);
				i--;
			}
		}
		//---PROJECTILE PHASE END

		//---POSITION PHASE
		player.isMoving = player.upPressed or player.rightPressed or player.downPressed or player.leftPressed;
		player.updatePosition(uni_clock.getElapsedTime().asSeconds());
		//---POSITION PHASE END

		//---COLLISION PHASE
		if (player.collisionCheck(objects.at(1), NULL))
		{
			if (currentLevel == 1)
			{
				levelLoad(&window, &objects, &entities, &currentLevel, 0, &textures);
				currentLevel = 0;
			}
			else
			{
				levelLoad(&window, &objects, &entities, &currentLevel, 1, &textures);
				currentLevel = 1;
			}
			continue;
		}

		float outline = objects.at(0).body.getOutlineThickness();
		FloatRect playerBounds(objects.at(0).body.getPosition(), WINDOW_SIZE - 2.f * Vector2f(outline, outline));
		player.collisionCheckInner(playerBounds);

		FloatRect cameraBounds(camera.getCenter() - camera.getSize() / 2.f, camera.getSize());

		// Interactions and Collisions
		bool interactionMessageDisplayed = false;
		bool needOverride = false;
		bool needOverride_t = false;
		for (size_t i = 1; i < objects.size(); i++)
		{			
			if (!objects.at(i).collisionCheck(cameraBounds))	//questionable
				continue;

			player.collisionCheck(objects.at(i), &needOverride_t);
			if (needOverride_t)
				needOverride = true;

			if (!interactionMessageDisplayed and player.interactionCheck(objects.at(i)))
			{
				if (interactionFlag)
				{
					if (objects.at(i).body.getFillColor() == Color::Green)
						objects.at(i).body.setFillColor(Color(Color::Black));
					else
						objects.at(i).body.setFillColor(Color(Color::Green));
					interactionFlag = false;
				}
				else
				{
					RectangleShape msg;
					msg.setSize(Vector2f(20, 5));
					msg.setPosition(Vector2f(player.body.getPosition() + Vector2f(0, -10)));
					msg.setFillColor(Color(Color::White));
					window.draw(msg);
					interactionMessageDisplayed = true;
				}
			}
		}
		if (!needOverride)
			player.overrideVector = Vector2f(0, 0);

		for (size_t i = 0; i < entities.size(); i++)
		{
			entities.at(i).script(Vector2f(400 + 100 * i, 300 + 100 * i), player.getCenter(), uni_clock.getElapsedTime().asSeconds(), &projectiles);
			for (size_t j = 1; j < objects.size(); j++)
			{
				entities.at(i).collisionCheck(objects.at(j));
			}
		}
		//---COLLISION PHASE END

		//---DRAW PHASE
		cameraCollision(&objects.at(0), &camera, &player, WINDOW_SIZE);
		window.setView(camera);

		int draws = 0;
		for (size_t i = 0; i < objects.size(); i++)
		{
			if (objects.at(i).collisionCheck(cameraBounds))
			{
				window.draw(objects.at(i).body);
				draws++;
			}
		}
		for (size_t i = 0; i < entities.size(); i++)
		{
			if (entities.at(i).collisionCheck(cameraBounds))
			{
				window.draw(entities.at(i).body);
				draws++;
			}
		}
		window.draw(player.body);
		for (size_t i = 0; i < projectiles.size(); i++)
		{
			if (projectiles.at(i).collisionCheck(cameraBounds))
			{
				window.draw(projectiles.at(i).body);
				draws++;
			}
		}

		cout << objects.size() + projectiles.size() + entities.size() << "  " << draws << endl;

		window.setView(minimap);
		for (size_t i = 0; i < objects.size(); i++)
		{
			if (objects.at(i).collisionCheck(cameraBounds))
			{
				Color color = objects.at(i).body.getFillColor();
				objects.at(i).body.setFillColor(Color(color.r, color.g, color.b, 150));
				window.draw(objects.at(i).body);
				objects.at(i).body.setFillColor(color);
			}
		}
		for (size_t i = 0; i < entities.size(); i++)
		{
			if (entities.at(i).collisionCheck(cameraBounds))
				window.draw(entities.at(i).body);
		}
		window.draw(player.body);
		for (size_t i = 0; i < projectiles.size(); i++)
		{
			if(projectiles.at(i).collisionCheck(cameraBounds))
				window.draw(projectiles.at(i).body);
		}
		
		window.display();
		//---DRAW PHASE END
	}

	return 0;
}


