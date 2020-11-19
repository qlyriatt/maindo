#pragma once
#include "Player.h"
#include "Map.h"


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
		player->setspeed((player->getbasespeed()) * (1 - 0.5 * state));
	}
} //let it beeeeeeeeeeeeeeee

void level_load(RenderWindow* window, vector<gameObject>* objects, int* currentLvl, int* switchLvl)
{
	if (*currentLvl != *switchLvl)
	{
		Clock clock;
		RectangleShape loadScreen;
		loadScreen.setSize(Vector2f(WINDOW_SIZE_X, WINDOW_SIZE_Y));
		loadScreen.setFillColor(Color(Color::Black));
		window->draw(loadScreen);
		window->display();

		objects->erase(objects->begin(), objects->end());
		*objects = initialize<gameObject>(*switchLvl);
		RectangleShape outerBounds = objects->at(0).body;
		float outline = outerBounds.getOutlineThickness();
		FloatRect playerBounds(outerBounds.getPosition(), Vector2f(window->getSize().x - 2 * outline, window->getSize().y - 2 * outline));
		*currentLvl = *switchLvl;

		for (; floor(clock.getElapsedTime().asSeconds() * 2) < 1;); //wait
		window->clear();
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
