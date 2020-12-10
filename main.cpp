#pragma once

#pragma warning (push)
#pragma warning (disable : 4244 4305)	//<----

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Weapon.h"
#include "gameObject.h"
#include "Misc.h"
#include "Map.h"
#include "Player.h"
#include "Entity.h"

using namespace std;
using namespace sf;

#define ESSENTIALS 2

// INPUT --> PROJECTILE --> POSITION --> COLLISION CHECK --> CAMERA --> DRAW
//	 ^													|
//   |------------------INPUT OVERRIDE-------------------
//
//							current

//it depends
struct gameTexture
{
	Texture* texture;
	int animationCycles;
};


int main()
{
	RenderWindow window(VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), pickName());
	RenderTexture mainGameTexture;
	mainGameTexture.create(WINDOW_SIZE.x, WINDOW_SIZE.y);
	
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
	board.hitboxSize = Vector2f(30, 25);
	board.hitboxPositions = { {-10,-20}, {25,-15}, {25,10}, {25,35} };
	
	Player player(Vector2f(20, 20), Vector2f(25, 60), &playerTexture, 200); //speed is pixels per second
	player.weapon = pistol;
	player.sprite.setTexture(*textures.at(0));
	bool switchedWeapon = false;
	
	int currentLevel = 1;
	bool drawMinimap = false;
	bool mainTextureCreated = true;
	levelLoad(&window, &objects, &entities, &currentLevel, 1, &textures);

	Clock mainClock;

	while (window.isOpen())
	{
		mainGameTexture.clear();
		window.clear();
		
		bool interactionFlag = false;
		Event event;

		//---INPUT PHASE
		while (window.pollEvent(event)) 
		{
			if (event.type == Event::Closed)
				window.close();

			else if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::E)
				{
					interactionFlag = true;
				}
				else if (event.key.code == Keyboard::R)
				{
					if (!player.isUsingWeapon)
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
				}
				else if (event.key.code == Keyboard::Z)
					camera.zoom(0.5);
				else if (event.key.code == Keyboard::X)
					camera.zoom(2);
				else if (event.key.code == Keyboard::M)
					drawMinimap = (drawMinimap ? false : true);
			}
			else if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::I)
					player.isInventoryOpen = true;
				else if (event.key.code == Keyboard::Escape)
				{
					float timestamp = mainClock.getElapsedTime().asSeconds();
					pause(&window, NULL);
					alignTime(timestamp, &mainClock, &player, &objects, &projectiles);
				}
			}
		}

		player.upPressed =			(Keyboard::isKeyPressed(Keyboard::W) ? true : false);
		player.rightPressed =		(Keyboard::isKeyPressed(Keyboard::D) ? true : false);
		player.downPressed =		(Keyboard::isKeyPressed(Keyboard::S) ? true : false);
		player.leftPressed =		(Keyboard::isKeyPressed(Keyboard::A) ? true : false);
		player.leftShiftPressed =	(Keyboard::isKeyPressed(Keyboard::LShift) ? true : false);

		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			player.weapon.action(&player, player.currentSight, player.getCenter() - Vector2f(0, 5), mainClock.getElapsedTime().asSeconds(), &projectiles);
			if (player.weapon.isMelee and !(getTimeDiff(&mainClock, player.weapon.latestShotTime) > player.weapon.projectileLifetime))
				player.isUsingWeapon = true; //false?
		}
		//---INPUT PHASE END

		//---PROJECTILE PHASE
		for (size_t i = 0; i < projectiles.size(); i++)
		{
			bool projectileErased = false;
			float traveledDistance = sqrt(pow(projectiles.at(i).currentPosition.x, 2) + pow(projectiles.at(i).currentPosition.y, 2)); //x^2 + y^2

			if (projectiles.at(i).isMelee)
			{
				if (mainClock.getElapsedTime().asSeconds() - projectiles.at(i).creationTime > projectiles.at(i).lifeTime)
				{
					//if (projectiles.at(i).gameObjectSource == &player)
					//{
					//	player.isUsingWeapon = false;
					//}
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
						Vector2f currentHitboxPosition = sourcePosition + hitboxes->at(getCount(getTimeDiff(&mainClock, projectiles.at(i).creationTime), hitboxes->size(), 2));
						projectiles.at(i).body.setPosition(currentHitboxPosition);
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
				projectiles.at(i).updatePosition(mainClock.getElapsedTime().asSeconds());

				for (size_t j = 1; j < objects.size(); j++)
				{
					if (projectiles.at(i).collisionCheck(objects.at(j)))
					{
						if (objects.at(j).isDestroyable)
						{
							//objects.at(j).hp -=
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
		player.updatePosition(mainClock.getElapsedTime().asSeconds());
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
					if (objects.at(i).interactionType == 1)
					{
						for (size_t j = 0; j < player.inventorySlots.size(); j++)
						{
							if (!player.inventorySlots.at(j))
							{
								player.inventorySlots.at(j) = objects.at(i).ID;
								objects.erase(objects.begin() + i);
								i--;
								break;
							}
						}
					}
					else
					{
						if (objects.at(i).body.getFillColor() == Color::Green)
							objects.at(i).body.setFillColor(Color(Color::Black));
						else
							objects.at(i).body.setFillColor(Color(Color::Green));
					}
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
			player.overrideInputX = player.overrideInputY = false;

		for (size_t i = 0; i < entities.size(); i++)
		{
			entities.at(i).script(Vector2f(400 + 100 * i, 300 + 100 * i), player.getCenter(), mainClock.getElapsedTime().asSeconds(), &projectiles);
			for (size_t j = 1; j < objects.size(); j++)
			{
				entities.at(i).collisionCheck(objects.at(j));
			}
		}
		//---COLLISION PHASE END

		//---DRAW PHASE
		player.updateAnimation(mainClock.getElapsedTime().asSeconds(), textures.at(0));

		cameraCollision(&objects.at(0), &camera, &player, WINDOW_SIZE);//Vector2f(mainGameTexture.getSize()));
		if (camera.getSize().x == CAMERA_SIZE.x / 8)
			camera.setCenter(player.getCenter() - Vector2f(0, 10));
		if (camera.getSize().x == CAMERA_SIZE.x / 16)
			camera.setCenter(player.getCenter() - Vector2f(0, 20));


		mainGameTexture.setView(camera);
		int drawCalls = 0;
		finalDraw(&mainGameTexture, &objects, &entities, &projectiles, &player, &drawCalls);
		
		//cout << objects.size() + projectiles.size() + entities.size() << " " << drawCalls << endl;
		mainGameTexture.display();

		if (player.isInventoryOpen)
		{
			float timestamp = mainClock.getElapsedTime().asSeconds();
			showInventory(&window, &mainGameTexture, &camera, &player);
			alignTime(timestamp, &mainClock, &player, &objects, &projectiles);
		}

		Sprite buf(mainGameTexture.getTexture());
		window.draw(buf);

		if (drawMinimap)
		{
			RenderTexture minimapTexture;
			minimapTexture.create(WINDOW_SIZE.x, WINDOW_SIZE.y);
			minimapTexture.setView(minimap);

			//finalDrawMinimap(&minimapTexture, &objects, &entities, &projectiles, &player);
			for (size_t i = 0; i < objects.size(); i++)
			{
				if (objects.at(i).collisionCheck(cameraBounds))
				{
					Color color = objects.at(i).body.getFillColor();
					objects.at(i).body.setFillColor(Color(color.r, color.g, color.b, 150));
					minimapTexture.draw(objects.at(i).body);
					objects.at(i).body.setFillColor(color);
				}
			}
			for (size_t i = 0; i < entities.size(); i++)
			{
				if (entities.at(i).collisionCheck(cameraBounds))
					minimapTexture.draw(entities.at(i).body);
			}
			minimapTexture.draw(player.body);
			for (size_t i = 0; i < projectiles.size(); i++)
			{
				if (projectiles.at(i).collisionCheck(cameraBounds))
					minimapTexture.draw(projectiles.at(i).body);
			}


			minimapTexture.display();
			Sprite buf(minimapTexture.getTexture());
			window.draw(buf);
		}
		window.display();
		//---DRAW PHASE END
	}

	return 0;
}


