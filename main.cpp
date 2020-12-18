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

enum ExitCodes
{
	windowClosedMain = 0,
	windowClosedFunction
};


// SPECIFY FOLDER WITH GAME FILES
const std::string DIRECTORY{ "D:/All mine/Game/Maindo/" };

int main()
{
	RenderWindow window(VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), pickName()/*,Style::Fullscreen*/);	

	Image* icon = new Image;
	icon->loadFromFile(DIRECTORY + "Textures/icon.png");
	window.setIcon(icon->getSize().x, icon->getSize().y, icon->getPixelsPtr());
	delete icon;

	View camera(FloatRect(Vector2f(0, 0), CAMERA_SIZE));
	camera.setViewport(FloatRect(0, 0, 1, 1));
	View minimap(FloatRect(Vector2f(0, 0), WINDOW_SIZE));
	minimap.setViewport(FloatRect(0.35, 0.7, 0.28, 0.28)); //0.03, 0.75, 0.2, 0.2
	
	RenderTexture mainGameTexture;
	mainGameTexture.create(WINDOW_SIZE.x, WINDOW_SIZE.y);
	RenderTexture minimapTexture;
	minimapTexture.create(WINDOW_SIZE.x, WINDOW_SIZE.y);

	Font fontMain;
	fontMain.loadFromFile(DIRECTORY + "VERYBADFONT.ttf");

	vector<Texture> texturesMenu;
	loadTexturesMenu(texturesMenu);
	vector<Texture> texturesPause;
	loadTexturesPause(texturesPause);

	vector<Texture> textures = loadTextures();

	vector<gameObject> objects;
	vector<Projectile> projectiles;
	vector<Entity> entities;


	//MELEE WEAPONS
	//
	//---ID---DAMAGE---ADDITIONAL PENETRATION---SWING DELAY---HITBOX LIFETIME---HITBOX POSITIONS---HITBOX SIZE---
	//
	// 1 / FIRERATE - HB LIFETIME == TIME BETWEEN SWINGS ----> 1 / FIRERATE SHOULD BE >= HB LIFETIME
	//
	//
	Vector2f hitboxSizeBoardStandart = { 30,25 };
	vector<Vector2f> hitboxesBoardStandart = { {-10,-20}, {25,-15}, {25,10}, {25,35} };
	Weapon board(1, 8, 1, 1, 0.7, hitboxesBoardStandart, hitboxSizeBoardStandart);

	// RANGED WEAPONS
	//
	//---ID---DAMAGE---ADDITIONAL PENETRATION---SHOT DELAY---RANGE---PROJECTILE SPEED---AMMO CAPACITY---RELOAD TIME---PROJECTILE TEXTURE---
	//
	//
	Weapon pistol(1, 8, 0, 0.5, 400, 400, 12, 1.5, textures.at(1));
	Weapon rifle(2, 12, 1, 0.3, 600, 600, 25, 2, textures.at(2));
	Weapon sniperRifle(4, 20, 2, 2, 800, 800, 5, 3, textures.at(2));



	
	board.actionSpriteOffset = Vector2i(10, 25);
	board.actionSpriteSize = Vector2i(65, 85);
	
	Player player(Vector2f(20, 20), Vector2f(40, 90), &textures.at(0), 200); //speed is pixels per second
	player.weapon = pistol;
	player.sprite.setTexture(textures.at(0));
	bool switchedWeapon = false;
	
	int currentLevel = 1;
	bool drawMinimap = true;
	bool mainTextureCreated = true;
	levelLoad(window, objects, entities, currentLevel, 1, textures);

	ifstream test1("D:/All mine/Game/test1.txt");
	if (!test1.is_open())
		cout << "TEST 1" << endl;
	ofstream test2("D:/All mine/Game/test2.txt");
	if (!test2.is_open())
		cout << "test 2 " << endl;

	bool inMenu = true;
	player.isUsingWeapon = false;

	Clock mainClock;
	Event event;
	while (window.isOpen())
	{
		window.clear();
		mainGameTexture.clear();
		bool interactionFlag = false;

		//---INPUT PHASE
		while (window.pollEvent(event)) 
		{
			if (event.type == Event::KeyPressed)
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
				else if (event.key.code == Keyboard::Hyphen)
					minimap.zoom(2);
				else if (event.key.code == Keyboard::Equal)
					minimap.zoom(0.5);
			}
			else if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::I)
					player.isInventoryOpen = true;
				else if (event.key.code == Keyboard::Escape)
				{
					float timestamp = mainClock.getElapsedTime().asSeconds();

					switch (showScreenPause(window, texturesPause, fontMain))
					{
					case -1: return -13;
					case 0: inMenu = true;
					case 1: break;
					case 2: saveLevel(currentLevel, objects, entities, textures);
					}
					alignTime(timestamp, mainClock, player, objects, projectiles);
				}
			}
			else if (event.type == Event::Closed)
			{
				window.close();
				return ExitCodes::windowClosedMain;
			}
		}

		if (inMenu)
		{
			objects.erase(objects.begin(), objects.end());
			entities.erase(entities.begin(), entities.end());
			projectiles.erase(projectiles.begin(), projectiles.end());

			switch (int chosenLevel = showScreenMenu(window, texturesMenu, fontMain))
			{
			case -1:
				return -15;
			case 0:
				//loadLevel(objects, currentLevel);
				break;
			default:
				levelLoad(window, objects, entities, currentLevel, chosenLevel, textures);
				break;
			}

			inMenu = false;
		}

		applyPlayerInput(player, projectiles, mainClock);
		//---INPUT PHASE END


		//---PROJECTILE PHASE

			//pre-remove of melee HB with expired swing or ranged projectiles with exceeding distance
			projectiles.erase(remove_if(projectiles.begin(), projectiles.end(), [mainClock](const Projectile& projectile)
			{ return projectile.isMelee and getTimeDiff(mainClock, projectile.creationTime) > projectile.lifeTime ? true :
			!projectile.isMelee and projectile.traveledDistance > projectile.range ? true : false; }), projectiles.end());


		for (size_t i = 0; i < projectiles.size(); i++)
		{
			if (projectiles.at(i).isMelee)
			{
				projectiles.at(i).body.setPosition(player.body.getPosition() + projectiles.at(i).swingHandle(mainClock));

				for (size_t j = 1; j < objects.size(); j++)
				{
					if (projectiles.at(i).collisionCheck(objects.at(j)) and objects.at(j).isDestroyable and projectiles.at(i).penetration)
					{
						projectiles.at(i).penetration--;
						objects.erase(objects.begin() + j);
						j--;
					}
				}
			}

			else 
			{
				projectiles.at(i).updatePosition(mainClock.getElapsedTime().asSeconds());
				projectiles.at(i).traveledDistance += projectiles.at(i).latestDistanceCovered;

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
								continue; //continue checking collisions for the same projectile
							}
						}

						projectiles.erase(projectiles.begin() + i);
						i--;
						break;
					}
				}
			}
		}

		player.weapon.reloadHandle(mainClock);
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
				levelLoad(window, objects, entities, currentLevel, 0, textures);
				currentLevel = 0;
			}
			else
			{
				levelLoad(window, objects, entities, currentLevel, 1, textures);
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
			entities.at(i).script(Vector2f(400 + 100 * i, 300 + 100 * i), player.getCenter(), mainClock.getElapsedTime().asSeconds(), projectiles);
			for (size_t j = 1; j < objects.size(); j++)
			{
				entities.at(i).collisionCheck(objects.at(j));
			}
		}
		//---COLLISION PHASE END

		//---DRAW PHASE
		player.updateAnimation(mainClock.getElapsedTime().asSeconds(), &textures.at(0));

		cameraCollision(objects.at(0), camera, player, WINDOW_SIZE); //Vector2f(mainGameTexture.getSize()));
		if (camera.getSize().x == CAMERA_SIZE.x / 8)
			camera.setCenter(player.getCenter() - Vector2f(0, 10));
		if (camera.getSize().x == CAMERA_SIZE.x / 16)
			camera.setCenter(player.getCenter() - Vector2f(0, 20));

		mainGameTexture.setView(camera);
		minimapTexture.setView(minimap);
		minimap.setCenter(player.getCenter());


		finalDraw(mainGameTexture, objects, entities, projectiles, player);
		mainGameTexture.display();


		if (player.isInventoryOpen)
		{			
			float timestamp = mainClock.getElapsedTime().asSeconds();
			//showScreenInventory(window, mainGameTexture, player);
			alignTime(timestamp, mainClock, player, objects, projectiles);
		}

		Sprite buf(mainGameTexture.getTexture());
		window.draw(buf);

		RectangleShape hpBase;
		hpBase.setPosition(30, 30);
		hpBase.setSize(Vector2f(102, 22));
		hpBase.setFillColor(Color::White);
		window.draw(hpBase);
		RectangleShape hpBar;
		hpBar.setPosition(31, 31);
		hpBar.setSize(Vector2f(player.health, 20));
		hpBar.setFillColor(Color::Red);
		window.draw(hpBar);


		if (drawMinimap)
		{
			finalDrawMinimap(minimapTexture, objects, entities, projectiles, player, cameraBounds);
			RectangleShape black;
			black.setPosition(window.getSize()* Vector2f{ minimap.getViewport().left, minimap.getViewport().top });
			black.setSize(window.getSize() * Vector2f{ minimap.getViewport().width, minimap.getViewport().height });
			black.setFillColor(Color(0,0,0, 180));
			black.setOutlineColor(Color::Red);
			black.setOutlineThickness(2);
			window.draw(black);
			window.draw(Sprite(minimapTexture.getTexture()));
		}
		window.display();
		//---DRAW PHASE END
	}

	return 0;
}


