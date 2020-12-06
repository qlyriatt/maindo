#pragma once

#pragma warning (push)
#pragma warning (disable : 4244 4305)	//<----

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
#define DEBUG_LEVEL 1

// INPUT --> PROJECTILE --> POSITION --> COLLISION CHECK --> CAMERA --> DRAW
//	 ^													|
//   |------------------INPUT OVERRIDE-------------------
//
//								current


struct gameTexture
{
	Texture* texture;
	int animationCycles;
};


int main()
{
	RenderWindow window(VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), pickName());
	
	View camera(FloatRect(Vector2f(0, 0), CAMERA_SIZE));
	camera.setViewport(FloatRect(0, 0, 1, 1));
	View minimap(FloatRect(Vector2f(0, 0), WINDOW_SIZE));
	minimap.setViewport(FloatRect(0.35, 0.7, 0.3, 0.3)); //0.03, 0.75, 0.2, 0.2

	vector<Texture*> textures;
	vector<gameObject> objects;
	vector<Projectile> projectiles;
	vector<Entity> entities;

	Texture playerTexture;
	playerTexture.loadFromFile("D:/All mine/Game/Maindo/player.png");
	textures.push_back(&playerTexture);
	Texture bulletRifleTexture;
	bulletRifleTexture.loadFromFile("D:/All mine/Game/bulletRifle.png");
	textures.push_back(&bulletRifleTexture);
	Texture bulletPistolTexture;
	bulletPistolTexture.loadFromFile("D:/All mine/Game/bulletPistol.png");
	textures.push_back(&bulletPistolTexture);

	Weapon sniperRifle(3, 800, 600, 5, &bulletRifleTexture, 1, 3);
	Weapon rifle(2, 600, 400, 30, &bulletRifleTexture, 5, 2);
	Weapon pistol(1, 200, 200, 15, &bulletPistolTexture, 3, 1.5);
	Weapon board(0, 0, 0, 0, NULL, 1, 0, 8);
	board.isMelee = true;
	board.projectileLifetime = 0.48;
	board.actionSpriteOffset = Vector2i(10, 25);
	board.actionSpriteSize = Vector2i(65, 85);
	board.hitboxSize = Vector2f(30, 20);
	board.hitboxPositions = { {0,-20},{30,-20},{30,0},{30,30} };
	

	Player player(Vector2f(20, 20), Vector2f(25, 60), &playerTexture, 200); //speed is pixels per second
	player.weapon = pistol;
	player.sprite.setTexture(*textures.at(0));
	bool switchedWeapon = false;
	
	int currentLevel = 1;
	bool drawMinimap = true;
	levelLoad(&window, &objects, &entities, &currentLevel, 1, &textures);
	Clock uni_clock;

	while (window.isOpen())
	{
		window.clear();

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
				else if (event.key.code == Keyboard::E)
				{
					interactionFlag = true;
				}
				else if (event.key.code == Keyboard::R)
				{
					if (switchedWeapon)
					{
						player.weapon = pistol;
						switchedWeapon = false;
					}
					else
					{
						player.weapon = board;
						switchedWeapon = true;
					}
				}
				else if (event.key.code == Keyboard::Z)
					camera.zoom(0.5);
				else if (event.key.code == Keyboard::X)
					camera.zoom(2);
				else if (event.key.code == Keyboard::M)
					drawMinimap = (drawMinimap ? false : true);
				
			}
		}

		player.upPressed = (Keyboard::isKeyPressed(Keyboard::W) ? true : false);
		player.rightPressed = (Keyboard::isKeyPressed(Keyboard::D) ? true : false);
		player.downPressed = (Keyboard::isKeyPressed(Keyboard::S) ? true : false);
		player.leftPressed = (Keyboard::isKeyPressed(Keyboard::A) ? true : false);
		player.leftShiftPressed = (Keyboard::isKeyPressed(Keyboard::LShift) ? true : false);

		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			player.weapon.action(&player, player.currentSight, player.getCenter() - Vector2f(0, 5), uni_clock.getElapsedTime().asSeconds(), &projectiles);
			if (player.weapon.isMelee)
				player.isUsingWeapon = true;
		}
		//---INPUT PHASE END

		//---PROJECTILE PHASE
		for (size_t i = 0; i < projectiles.size(); i++)
		{
			bool projectileErased = false;
			float traveledDistance = sqrt(pow(projectiles.at(i).currentPosition.x, 2) + pow(projectiles.at(i).currentPosition.y, 2)); //x^2 + y^2

			if (projectiles.at(i).isMelee)
			{
				if (uni_clock.getElapsedTime().asSeconds() - projectiles.at(i).creationTime > projectiles.at(i).lifeTime)
				{
					if (projectiles.at(i).gameObjectSource == &player)
					{
						player.isUsingWeapon = false;
					}
					cout << "melee erased" << endl;
					projectiles.erase(projectiles.begin() + i);
					i--;
				}
				else
				{
					vector<Vector2f>* hitboxes = &((Weapon*)projectiles.at(i).weaponSource)->hitboxPositions;
					Vector2f sourcePosition = ((gameObject*)projectiles.at(i).gameObjectSource)->body.getPosition(); //just plain terribleness
					if (hitboxes->size() > 1)
					{
						//wtf
						Vector2f currentHitboxPosition = sourcePosition + hitboxes->at(getCount(getTimeDiff(&uni_clock, projectiles.at(i).creationTime), hitboxes->size(), 2));
						projectiles.at(i).body.setPosition(currentHitboxPosition);

						cout << sourcePosition.x << " " << sourcePosition.y << endl; //<-----
						cout << currentHitboxPosition.x << " " << currentHitboxPosition.y << endl;
					}

					for (size_t j = 1; j < objects.size(); j++)
					{
						if (projectiles.at(i).collisionCheck(objects.at(j)) and objects.at(j).isDestroyable)
						{
							objects.erase(objects.begin() + j);
							j--;
						}
					}
				}
			}
			else if (traveledDistance < projectiles.at(i).range)
			{
				projectiles.at(i).updatePosition(uni_clock.getElapsedTime().asSeconds());

				for (size_t j = 1; j < objects.size(); j++)
				{
					if (projectiles.at(i).collisionCheck(objects.at(j)))
					{
						if (objects.at(j).isDestroyable)
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
			//if (!objects.at(i).collisionCheck(cameraBounds))	//questionable
			//	continue;
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
		{
			player.overrideInputX = false;
			player.overrideInputY = false;
		}

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
		player.updateAnimation(uni_clock.getElapsedTime().asSeconds(), textures.at(0));

		cameraCollision(&objects.at(0), &camera, &player, WINDOW_SIZE);
		if (camera.getSize().x == CAMERA_SIZE.x / 8)
			camera.setCenter(player.getCenter() - Vector2f(0, 10));
		if (camera.getSize().x == CAMERA_SIZE.x / 16)
			camera.setCenter(player.getCenter() - Vector2f(0, 20));

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
		for (size_t i = 0; i < projectiles.size(); i++)
		{
			if (projectiles.at(i).collisionCheck(cameraBounds))
			{
				if (projectiles.at(i).isMelee and DEBUG_LEVEL)
					projectiles.at(i).body.setFillColor(Color(255, 255, 255, 150));

				window.draw(projectiles.at(i).body);
				draws++;
			}
		}

		if (DEBUG_LEVEL)
		{
			RectangleShape a;
			a.setPosition(player.body.getPosition());
			a.setSize(player.body.getSize());
			a.setFillColor(Color(255, 0, 0, 150));
			window.draw(a);
			a.setPosition(player.sprite.getPosition());
			a.setSize(Vector2f(player.sprite.getGlobalBounds().width, player.sprite.getGlobalBounds().height));
			a.setFillColor(Color(0, 255, 0, 70));
			window.draw(a);
		}
		window.draw(player.sprite);
		cout << player.sprite.getPosition().x << " " << player.sprite.getPosition().y << endl;
		//cout << player.body.getPosition().x << " " << player.body.getPosition().y << endl;
		//cout << objects.size() + projectiles.size() + entities.size() << "  " << draws << endl;
		if (drawMinimap)
		{
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
				if (projectiles.at(i).collisionCheck(cameraBounds))
					window.draw(projectiles.at(i).body);
			}
		}
		window.display();
		//---DRAW PHASE END
	}

	return 0;
}


