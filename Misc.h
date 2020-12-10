#pragma once
#include "Player.h"
#include "Map.h"
#include <time.h>
using std::vector;

const Vector2f WINDOW_SIZE{ 800,600 };
const Vector2f CAMERA_SIZE{ WINDOW_SIZE / 2.f };
const Vector2f INVENTORY_SIZE{ CAMERA_SIZE / 2.f };
#define DEBUG_LEVEL 1

//every possible use(less)(ful) function that can be thought of

String pickName()
{
	srand(time(0));

	vector<String> names;

	names.push_back("VeryGoodGame");
	names.push_back("Maindo");
	names.push_back("Unfinished");
	names.push_back("what");
	names.push_back("Why are we still here");
	names.push_back("ovhl 1.xx <----> this string is useless");
	names.push_back("LOL LOL LOL LOL LOL LOL");
	names.push_back("Mine is better");
	names.push_back("Also try Terraria!");
	names.push_back("When I was / A young boy / My father / Took me into the city");
	names.push_back("Hajimemashite, chikyuujin-san!");
	names.push_back("Cookie ^_^");
	names.push_back("Ore wa Emilia ga suki da");
	names.push_back("My neck, my back...");
	names.push_back("3 things I hate in life: 1.Lists 2.C++ 3.Irony");
	names.push_back("Also try Minecraft!");
	names.push_back("Warning C4244: 'argument': conversion from 'int' to 'T', possible loss of data");
	names.push_back("<-----DO NOT TOUCH----->");
	names.push_back("Eighth Wonder of the World");
	names.push_back("Sometimes I pull so hard on it, I rip the skin");
	names.push_back("Angrily taking a shit");
	names.push_back("You want my property - you can't have it!");
	names.push_back("Dorimin chuchu / Chocola-ta-ta-ta-ta!");
	names.push_back("Certainly not a case of lupus");
	names.push_back("Soretomo... wa - ta - shi?");
	names.push_back("...'Cause we'll be doing this till 6 in the morning"); //whoops
	names.push_back("Full sail ahead!");
	names.push_back("cout << vector.x << " " << vector.y << endl;");
	names.push_back("For $%@^$%^# sake, would you work already?");
	names.push_back("NULL");
	names.push_back("JOJO!-da-da-da-dum-dum-dum-dum-dum-GOLD WIND!");
	names.push_back("Bangarang!");
	names.push_back("This game is not suitable for children or those who are easily disturbed");
	names.push_back("");
	names.push_back("It's because the heart of mine has made it here before my body");
	names.push_back("Seven circles of OOP");
	names.push_back("Sleep is overrated");
	names.push_back("Number 15: Burger King foot lettuce");
	names.push_back("Oyasumi");
	names.push_back("Back in the zenzenzense till this day been looking everywhere for you...");

	return names.at(rand() % names.size());
}

//aligns latestTimeUpdate (or else) for everything after additional rendering
void alignTime(float timestamp, Clock* clock, Player* player, vector<gameObject>* objects, vector<Projectile>* projectiles)
{
	for (size_t i = 0; i < objects->size(); i++)
	{
		objects->at(i).latestUpdate = clock->getElapsedTime().asSeconds();
		objects->at(i).latestAnimationUpdate = clock->getElapsedTime().asSeconds();
	}
	for (size_t i = 0; i < projectiles->size(); i++)
	{
		projectiles->at(i).latestUpdate = clock->getElapsedTime().asSeconds();
		projectiles->at(i).creationTime = clock->getElapsedTime().asSeconds() - (timestamp - projectiles->at(i).creationTime);
	}

	// aCT += eT 21 - lAU 20.5; count = 3; aCT += eT 48 - lAU 21(48); aCT += eT 48.5 - aCT 48; count = 4
	player->latestUpdate = clock->getElapsedTime().asSeconds();
	player->latestAnimationUpdate = clock->getElapsedTime().asSeconds();
	player->weapon.latestShotTime = clock->getElapsedTime().asSeconds() - (timestamp - player->weapon.latestShotTime);
}

void showInventory(RenderWindow* window, const RenderTexture* mainGameTexture, const View* camera, Player* player)
{
	//everything you can tweak to change inventory appearance
	const int ITEM_ROWS = 2;
	const int ITEM_COLUMNS = 4;
	const Vector2f INVENTORY_POSITION = Vector2f(window->getSize()) / 4.f;
	const Vector2f INVENTORY_SIZE = Vector2f(window->getSize()) / 2.f;
	const Vector2f ITEM_BASE_OFFSET = Vector2f(INVENTORY_SIZE.x / ITEM_COLUMNS / 4, INVENTORY_SIZE.y / ITEM_ROWS / 4);
	const Vector2f ITEM_BASE_SIZE = 2.f * ITEM_BASE_OFFSET;
	
	//everything waiting to be drawn behind inventory textures
	const Sprite pendingDrawSprite = Sprite(mainGameTexture->getTexture());



	int chosenItem = 0;
	bool redraw = true;
	while (true)
	{
		Event event;
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window->close();
				return;
			}
			else if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::I)
				{
					player->isInventoryOpen = false;
					return;
				}
				else if (event.key.code == Keyboard::W)
				{
					if (chosenItem < ITEM_COLUMNS)
						chosenItem += ITEM_COLUMNS * (ITEM_ROWS - 1);
					else
						chosenItem -= ITEM_COLUMNS;
				}
				else if (event.key.code == Keyboard::S)
				{
					if (chosenItem > ITEM_COLUMNS * (ITEM_ROWS - 1) - 1)
						chosenItem -= ITEM_COLUMNS * (ITEM_ROWS - 1);
					else
						chosenItem += ITEM_COLUMNS;
				}
				else if (event.key.code == Keyboard::A)
				{
					if (chosenItem % ITEM_COLUMNS == 0)
						chosenItem += ITEM_COLUMNS - 1;
					else
						chosenItem--;
				}
				else if (event.key.code == Keyboard::D)
				{
					if (chosenItem % ITEM_COLUMNS == ITEM_COLUMNS - 1)
						chosenItem -= ITEM_COLUMNS - 1;
					else
						chosenItem++;
				}
				else if (event.key.code == Keyboard::E)
				{
					player->inventorySlots.at(chosenItem) = 0;
				}
				redraw = true;	//redraw on chosen item change
			}
		}

		if (redraw)
		{
			window->draw(pendingDrawSprite); //draw background

			//create inventory texture 
			RenderTexture inventoryTextureBase;
			inventoryTextureBase.create(window->getSize().x, window->getSize().y);

			RectangleShape tintedScreen;
			tintedScreen.setSize(Vector2f(inventoryTextureBase.getSize()));
			tintedScreen.setFillColor(Color(0, 0, 0, 140));
			inventoryTextureBase.draw(tintedScreen);

			RectangleShape inventoryShape;
			inventoryShape.setSize(Vector2f(inventoryTextureBase.getSize()) / 2.f);
			inventoryShape.setPosition(Vector2f(inventoryTextureBase.getSize()) / 4.f);
			inventoryShape.setFillColor(Color(255, 0, 0, 180));
			inventoryTextureBase.draw(inventoryShape);

			for (int i = 0; i < ITEM_ROWS; i++)
			{
				for (int j = 0; j < ITEM_COLUMNS; j++)
				{
					RectangleShape obj;
					obj.setPosition(INVENTORY_POSITION + Vector2f(j * INVENTORY_SIZE.x / ITEM_COLUMNS, i * INVENTORY_SIZE.y / ITEM_ROWS) + ITEM_BASE_OFFSET);
					obj.setSize(ITEM_BASE_SIZE);

					if (i == int(chosenItem / ITEM_COLUMNS) and j == chosenItem % ITEM_COLUMNS)
					{
						RectangleShape frame = obj;
						frame.setOutlineColor(Color::Green);
						frame.setOutlineThickness(3);
						inventoryTextureBase.draw(frame);
					}
					if (player->inventorySlots.at(j + i * ITEM_COLUMNS))
						obj.setFillColor(Color::Blue);
					else
					{
						obj.setFillColor(Color::Black);
					}

					inventoryTextureBase.draw(obj);
				}
			}
			inventoryTextureBase.display();
			Sprite inventorySpriteBase(inventoryTextureBase.getTexture());
			
			window->draw(inventorySpriteBase);
			window->display();
			redraw = false;
			//done redrawing
		}
	}
}

void finalDraw(RenderTarget* renderTarget, vector<gameObject>* objects, vector<Entity>* entities, vector<Projectile>* projectiles, Player* player, int* drawCalls = NULL) 
{
	FloatRect cameraBounds(renderTarget->getView().getCenter() - renderTarget->getView().getSize() / 2.f, renderTarget->getView().getSize());

	for (size_t i = 0; i < objects->size(); i++)
	{
		if (objects->at(i).collisionCheck(cameraBounds))
		{
			renderTarget->draw(objects->at(i).body);
			if(drawCalls)
				(*drawCalls)++;
		}
	}

	for (size_t i = 0; i < entities->size(); i++)
	{
		if (entities->at(i).collisionCheck(cameraBounds))
		{
			renderTarget->draw(entities->at(i).body);
			if(drawCalls)
				(*drawCalls)++;
		}
	}

	for (size_t i = 0; i < projectiles->size(); i++)
	{
		if (projectiles->at(i).collisionCheck(cameraBounds))
		{
			if (projectiles->at(i).isMelee and DEBUG_LEVEL)
				projectiles->at(i).body.setFillColor(Color(255, 255, 255, 150));

			renderTarget->draw(projectiles->at(i).body);
			if(drawCalls)
				(*drawCalls)++;
		}
	}

	if (DEBUG_LEVEL)
	{
		RectangleShape tmp;
		tmp.setPosition(player->body.getPosition());
		tmp.setSize(player->body.getSize());
		tmp.setFillColor(Color(255, 0, 0, 150));
		renderTarget->draw(tmp);
		tmp.setPosition(player->sprite.getPosition());
		tmp.setSize(Vector2f(player->sprite.getGlobalBounds().width, player->sprite.getGlobalBounds().height));
		tmp.setFillColor(Color(0, 255, 0, 70));
		renderTarget->draw(tmp);
	}
	renderTarget->draw(player->sprite);

}

void setOpacity(gameObject* object, int opacity = 255)
{
	Color tmp = object->body.getFillColor();
	object->body.setFillColor(Color(tmp.r, tmp.g, tmp.b, opacity));
}

void finalDrawMinimap(RenderTarget* renderTarget, vector<gameObject>* objects, vector<Entity>* entities, vector<Projectile>* projectiles, Player* player)
{
	for (size_t i = 0; i < objects->size(); i++)
	{
		setOpacity(&objects->at(i), 150);
		renderTarget->draw(objects->at(i).body);
		setOpacity(&objects->at(i));
	}

	for (size_t i = 0; i < entities->size(); i++)
	{
		setOpacity(&entities->at(i), 150);
		renderTarget->draw(entities->at(i).body);
		setOpacity(&entities->at(i));
	}
	for (size_t i = 0; i < projectiles->size(); i++)
	{
		setOpacity(&projectiles->at(i), 150);
		renderTarget->draw(projectiles->at(i).body);
		setOpacity(&projectiles->at(i));
	}
	renderTarget->draw(player->sprite);
	//setOpacity(player, 150);
}

float getTimeDiff(Clock* clock, float time)
{
	return clock->getElapsedTime().asSeconds() - time;
}

int getCount(float storedTimeDifference, int animationStates, int changesPerSecondMultiplier = 1)
{
	int a = floor(storedTimeDifference * animationStates * changesPerSecondMultiplier);
	for (size_t i = 0; i < changesPerSecondMultiplier; i++)
	{
		a %= animationStates;
	}
	return a;
}

void levelLoad(RenderWindow* window, vector<gameObject>* objects, vector<Entity>* entities, int* currentLevel, int switchToLevel, vector<Texture*>* textures)
{
	Clock clock;

	RectangleShape loadScreen;
	loadScreen.setSize(Vector2f(window->getSize()));
	loadScreen.setFillColor(Color(Color::Black));
	window->draw(loadScreen);
	window->display();

	objects->erase(objects->begin(), objects->end());
	entities->erase(entities->begin(), entities->end());
	initialize(switchToLevel, objects, entities, textures);
	*currentLevel = switchToLevel;

	for (; floor(clock.getElapsedTime().asSeconds() * 2) < 2;); //wait
	window->clear();
}

void cameraCollision(gameObject* area, View* camera, Player* player, Vector2f WINDOW_SIZE)
{
	camera->setCenter(player->getCenter());
	const FloatRect allowedCameraArea = area->body.getGlobalBounds();
	const Vector2f cameraPosition = camera->getCenter() - camera->getSize() / 2.f;

	bool TL = allowedCameraArea.contains(cameraPosition); 
	bool TR = allowedCameraArea.contains(cameraPosition + Vector2f(camera->getSize().x, 0));
	bool BL = allowedCameraArea.contains(cameraPosition + Vector2f(0, camera->getSize().y));
	bool BR = allowedCameraArea.contains(cameraPosition + camera->getSize());

	if (!(TL and TR and BL and BR))
	{
		if (TL)
		{
			if (BL)
				camera->setCenter(Vector2f(WINDOW_SIZE.x - camera->getSize().x / 2, player->getCenter().y));
			else if (TR)
				camera->setCenter(Vector2f(player->getCenter().x, WINDOW_SIZE.y - camera->getSize().y / 2));
			else
				camera->setCenter(WINDOW_SIZE - camera->getSize() / 2.f);
		}

		else if (BR)
		{
			if (TR)
				camera->setCenter(Vector2f(camera->getSize().x / 2, player->getCenter().y));
			else if (BL)
				camera->setCenter(Vector2f(player->getCenter().x, camera->getSize().y / 2));
			else
				camera->setCenter(camera->getSize() / 2.f);
		}

		else if (BL)
			camera->setCenter(Vector2f(WINDOW_SIZE.x - camera->getSize().x / 2, camera->getSize().y / 2));
		else if (TR)
			camera->setCenter(Vector2f(camera->getSize().x / 2, WINDOW_SIZE.y - camera->getSize().y / 2));
		else
			camera->setCenter(player->getCenter()); // precaution
	}
}

//should be merged with showInventory ???
void pause(RenderWindow* window, vector<Texture>* textures)
{
	const int ROWS = 4;
	const int COLUMNS = 1;
	const float	BUTTON_SPACING = 10;
	const Vector2f BUTTON_SIZE{ 200, 30 };
	const Vector2f BUTTON_OFFSET{ window->getSize().x / 2 - BUTTON_SIZE.x / 2,window->getSize().y / 2 - (ROWS - 1) / 2 * BUTTON_SPACING - ROWS * BUTTON_SIZE.y };

	RenderTexture pauseTexture;
	pauseTexture.create(window->getSize().x, window->getSize().y);


	int chosenButton = 0;
	bool redraw = true;
	Event event;

	while (true)
	{
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window->close();
				return;
			}
			else if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Escape)
				{
					return;
				}
				else if (event.key.code == Keyboard::W)
				{
					if (chosenButton < COLUMNS)
						chosenButton += COLUMNS * (ROWS - 1);
					else
						chosenButton -= COLUMNS;
				}
				else if (event.key.code == Keyboard::S)
				{
					if (chosenButton > COLUMNS * (ROWS - 1) - 1)
						chosenButton -= COLUMNS * (ROWS - 1);
					else
						chosenButton += COLUMNS;
				}
				else if (event.key.code == Keyboard::A)
				{
					if (chosenButton % COLUMNS == 0)
						chosenButton += COLUMNS - 1;
					else
						chosenButton--;
				}
				else if (event.key.code == Keyboard::D)
				{
					if (chosenButton % COLUMNS == COLUMNS - 1)
						chosenButton -= COLUMNS - 1;
					else
						chosenButton++;
				}
				redraw = true;
			}
		}

		if (redraw)
		{
			window->clear();
			pauseTexture.clear();

			RectangleShape blackScreen;
			blackScreen.setSize(Vector2f(window->getSize()));
			blackScreen.setFillColor(Color(20,30,20));
			pauseTexture.draw(blackScreen);

			for (int i = 0; i < ROWS; i++)
			{
				for (int j = 0; j < COLUMNS; j++)
				{
					RectangleShape obj;
					obj.setPosition(BUTTON_OFFSET + Vector2f(0, (BUTTON_SIZE.y + BUTTON_SPACING) * i));
					obj.setSize(BUTTON_SIZE);
					if (i == int(chosenButton / COLUMNS) and j == chosenButton % COLUMNS)
					{
						obj.setFillColor(Color::White);
					}
					else
						obj.setFillColor(Color::Blue);
					pauseTexture.draw(obj);
				}
			}

			pauseTexture.display();
			Sprite pauseSpriteBase(pauseTexture.getTexture());

			window->draw(pauseSpriteBase);
			window->display();
			redraw = false;
			//done redrawing
		}
	}
}