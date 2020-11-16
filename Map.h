#pragma once
#include "Player.h"
#include <vector>


const int WINDOW_SIZE_X = 800;
const int WINDOW_SIZE_Y = 600;

template<class T>
vector<T> initialize(int map_type)
{
	switch (map_type)
	{
		case 1:
		{

		vector<T> objects1;

		RectangleShape outerBounds;
		float outline = 4;

		//overall map bounds
		outerBounds.setSize(Vector2f(WINDOW_SIZE_X - 2 * outline, WINDOW_SIZE_Y - 2 * outline));
		outerBounds.setPosition(Vector2f(outline, outline));
		outerBounds.setOutlineThickness(outline);
		outerBounds.setOutlineColor(Color(Color::Red));
		outerBounds.setFillColor(Color(Color::White));

		//obstacle 1
		RectangleShape mapBounds;
		mapBounds.setPosition(WINDOW_SIZE_X / 4, WINDOW_SIZE_Y / 4);
		mapBounds.setSize(Vector2f(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2));
		mapBounds.setOutlineThickness(4);
		mapBounds.setFillColor(Color(50, 20, 20));
		mapBounds.setOutlineColor(Color(255, 0, 0));

		objects1.push_back(outerBounds);
		objects1.push_back(mapBounds);

		//s
		for (short int i = 0; i < 10; i++)
		{
			RectangleShape obj;
			obj.setSize(Vector2f(20, 20));
			obj.setFillColor(Color(Color::Black));
			obj.setOutlineColor(Color(Color::Red));
			obj.setOutlineThickness(4);

			obj.setPosition(Vector2f(100 + 60 * i, 50));
			objects1.push_back(obj);
		}

		for (short int i = 0; i < 10; i++)
		{
			RectangleShape obj;
			obj.setSize(Vector2f(5, 5));
			obj.setFillColor(Color(Color::Black));
			obj.setOutlineColor(Color(Color::Green));
			obj.setOutlineThickness(4);

			obj.setPosition(Vector2f(30, 200 + i * 30));
			objects1.push_back(obj);
		}

		for (short int i = 0; i < 5; i++)
		{
			RectangleShape obj;
			obj.setSize(Vector2f(5, 5));
			obj.setFillColor(Color(Color::Black));
			obj.setOutlineColor(Color(Color::Green));
			obj.setOutlineThickness(4);

			obj.setPosition(Vector2f(30 + i*20, 200));
			objects1.push_back(obj);
		}


		return objects1;
	}
		default:
			break;
	}

};