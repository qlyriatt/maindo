#pragma once
#include "Player.h"
#include "Map.h"
#include <time.h>


String pickName()
{
	srand(time(0));

	String window[11];

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

	return window[rand() % 11];
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

