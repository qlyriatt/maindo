#pragma once
#include "Player.h"
#include "Map.h"
#include <time.h>

const Vector2f WINDOW_SIZE{ 800,600 };
const Vector2f CAMERA_SIZE{ WINDOW_SIZE / 2.f };
const Vector2f INVENTORY_SIZE{ CAMERA_SIZE / 2.f };

String pickName()
{
	srand(time(0));

	String window[12];

	window[0] = "VeryGoodGame";
	window[1] = "Maindo";
	window[2] = "Unfinished";
	window[3] = "what";
	window[4] = "Why are we still here";
	window[5] = "ovhl 1.xx <----> this string is useless";
	window[6] = "LOL LOL LOL LOL LOL LOL";
	window[7] = "Mine is better";
	window[8] = "Also try Terraria!";
	window[9] = "When I was/A young boy/My father/Took me into the city";
	window[10] = "Hajimemashite, chikyuujin-san!";
	window[11] = "Chocolate cookie ^_^";

	return window[rand() % 12];
}



void showInventory(RenderWindow* window, RenderTexture* mainGameTexture, View* camera, Player* player)
{
	const int ITEM_ROWS = 2;
	const int ITEM_COLUMNS = 4;
	const Vector2f INVENTORY_POSITION = Vector2f(window->getSize()) / 4.f;
	const Vector2f INVENTORY_SIZE = Vector2f(window->getSize()) / 2.f;
	const Vector2f ITEM_BASE_OFFSET = Vector2f(INVENTORY_SIZE.x / ITEM_COLUMNS / 4, INVENTORY_SIZE.y / ITEM_ROWS / 4);
	const Vector2f ITEM_BASE_SIZE = 2.f * ITEM_BASE_OFFSET;
	const Sprite pendingDrawSprite = Sprite(mainGameTexture->getTexture());
	//mainGameTexture->getTexture().copyToImage().saveToFile("D:/All mine/Game/tmp.png");

	int chosenItem = 0;
	bool redraw = true;
	while (true)
	{
		Event event;
		while (window->pollEvent(event))
		{
			cout << "ITEM" << chosenItem << "EVENT" << window->pollEvent(event) << endl;

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
				redraw = true;
			}
		}

		if (redraw)
		{
			window->draw(pendingDrawSprite);

			RenderTexture inventoryTextureBase;
			inventoryTextureBase.create(window->getSize().x, window->getSize().y);

			//cout << camera->getSize().x << " " << camera->getSize().y << " " << camera->getCenter().x << " " << camera->getCenter().y << endl;
			//cout << pendingDrawSprite.getGlobalBounds().width << " " << pendingDrawSprite.getGlobalBounds().height << endl;
			//cout << (camera->getCenter() - camera->getSize() / 2.f).x << " " << (camera->getCenter() - camera->getSize() / 2.f).y << endl;

			RectangleShape tintedScreen;
			tintedScreen.setSize(Vector2f(inventoryTextureBase.getSize()));
			tintedScreen.setPosition(0, 0);
			tintedScreen.setFillColor(Color(0, 0, 0, 150));
			inventoryTextureBase.draw(tintedScreen);

			RectangleShape inventoryShape;
			inventoryShape.setSize(Vector2f(inventoryTextureBase.getSize()) / 2.f);
			inventoryShape.setPosition(Vector2f(inventoryTextureBase.getSize()) / 4.f);
			inventoryShape.setFillColor(Color(255, 0, 0, 120));
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
						obj.setFillColor(Color::White);
					}
					else
						obj.setFillColor(Color::Blue);
					inventoryTextureBase.draw(obj);
				}
			}

			inventoryTextureBase.display();
			//inventoryTextureBase.getTexture().copyToImage().saveToFile("D:/All mine/Game/tmp.png");

			Sprite inventorySprite(inventoryTextureBase.getTexture());
			//inventorySprite.setPosition(camera->getCenter() - camera->getSize() / 2.f);
			cout << inventorySprite.getGlobalBounds().left << " " << inventorySprite.getGlobalBounds().top << endl;
			
			window->draw(inventorySprite);
			window->display();
			redraw = false;
		}
	}
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

//clever but not clever enough
void movement_handler(Event* event, Player* player, int state)
{
	if (event->key.code == Keyboard::W)
		player->upPressed = state;
	else if (event->key.code == Keyboard::D)
		player->rightPressed = state;
	else if (event->key.code == Keyboard::S)
		player->downPressed = state;
	else if (event->key.code == Keyboard::A)
		player->leftPressed = state;
	else if (event->key.code == Keyboard::LShift)
	{
		player->leftShiftPressed = state;
		player->speed = player->baseSpeed * (1 - 0.5 * state);
	}
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

// modified collisionCheckInner
void cameraCollision(gameObject* area_obj, View* camera, Player* player, Vector2f WINDOW_SIZE)
{
	FloatRect area = area_obj->body.getGlobalBounds();
	camera->setCenter(player->getCenter());
	Vector2f cameraPosition = camera->getCenter() - camera->getSize() / 2.f;
	bool TL = area.contains(cameraPosition);
	bool TR = area.contains(cameraPosition + Vector2f(camera->getSize().x, 0));
	bool BL = area.contains(cameraPosition + Vector2f(0, camera->getSize().y));
	bool BR = area.contains(cameraPosition + camera->getSize());

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

void pause(RenderWindow* window, Player* player, View* camera)
{
	bool pause = true;
	RectangleShape pauseScreen;
	pauseScreen.setSize(Vector2f(window->getSize().x, window->getSize().y));
	pauseScreen.setFillColor(Color(0, 0, 0, 150));
	window->draw(pauseScreen);

	vector<RectangleShape> pauseButtons;
	for (short int i = 0; i < 3; i++)
	{
		RectangleShape button;
		button.setSize(Vector2f(80, 10));
		button.setFillColor(Color(Color::White));
		button.setPosition(Vector2f(camera->getCenter().x - 40, camera->getCenter().y - 35 + 30 * i));
		pauseButtons.push_back(button);
		window->draw(button);
	}
	window->display();

	Event event;
	while (window->pollEvent(event) or pause)
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Escape)
				pause = false;
			else movement_handler(&event, player, 1);
		}

		if (event.type == Event::KeyReleased)
		{
			movement_handler(&event, player, 0);
		}
	}

}

