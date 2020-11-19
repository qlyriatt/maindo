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
	case 0:
	{
		vector<T> objects0;

		float outline = 4;

		gameObject outerBounds(0, Vector2f(outline, outline), Vector2f(WINDOW_SIZE_X - 2 * outline, WINDOW_SIZE_Y - 2 * outline));

		gameObject exit(0, Vector2f(50, 50), Vector2f(25, 25));

		objects0.push_back(outerBounds);
		objects0.push_back(exit);
		return objects0;
	}
	case 1:
	{
		vector<T> objects1;

		//overall map shape
		float outline = 4;

		gameObject outerBounds(0, Vector2f(outline, outline), Vector2f(WINDOW_SIZE_X - 2 * outline, WINDOW_SIZE_Y - 2 * outline));
		
		gameObject exit(0, Vector2f(100, 100), Vector2f(25, 25));
		
		gameObject mapBounds(0, Vector2f(WINDOW_SIZE_X / 4, WINDOW_SIZE_Y / 4), Vector2f(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2));

		objects1.push_back(outerBounds);
		objects1.push_back(exit);
		objects1.push_back(mapBounds);

		
		for (short int i = 0; i < 10; i++)
		{
			gameObject obj(0, Vector2f(100 + 60 * i, 50), Vector2f(20, 20));
			obj.body.setFillColor(Color(Color::Black));
			objects1.push_back(obj);
		}

		for (short int i = 0; i < 10; i++)
		{
			gameObject obj(0, Vector2f(30, 200 + i * 30), Vector2f(5, 5), false, Color::Green);
			obj.body.setFillColor(Color(Color::Black));
			objects1.push_back(obj);
		}

		for (short int i = 0; i < 5; i++)
		{
			gameObject obj(0, Vector2f(30 + i * 20, 200), Vector2f(5, 5), false, Color::Green);
			obj.body.setFillColor(Color(Color::Black));
			objects1.push_back(obj);
		}


		return objects1;

	}
	
	default:
	{
		vector<T> objects_empty;
		return objects_empty;
	}

	}

};