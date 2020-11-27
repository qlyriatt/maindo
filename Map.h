#pragma once
#include "gameObject.h"
#include <vector>

using namespace std;

#define WINDOW_SIZE_X 800
#define WINDOW_SIZE_Y 600

//prevents a mess by creating a new one instead
//should really be removed


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
		outerBounds.body.setFillColor(Color(20,20,50));

		gameObject exit(0, Vector2f(20, 50), Vector2f(25, 25));
		exit.body.setFillColor(Color(Color::Blue));

		gameObject att(50, Vector2f(350, 250), Vector2f(20, 20));
		att.body.setOutlineThickness(0);
		objects0.push_back(outerBounds);
		objects0.push_back(exit);
		objects0.push_back(att);

		for (int i = 0; i < 3; i++)
		{
			gameObject obj(0, Vector2f(300 + rand() % 300, 300 + rand() % 300), Vector2f(rand() % 20, rand() % 20));
			obj.body.setFillColor(Color(20 * i, 30 * i, 50 * i));
			objects0.push_back(obj);
		}
		
		gameObject node1(0, Vector2f(393, 293), Vector2f(10, 10), 1);
		objects0.push_back(node1);
		return objects0;
	}
	case 1:
	{
		vector<T> objects1;

		//overall map shape
		float outline = 4;

		gameObject outerBounds(0, Vector2f(outline, outline), Vector2f(WINDOW_SIZE_X - 2 * outline, WINDOW_SIZE_Y - 2 * outline));
		outerBounds.body.setFillColor(Color(20, 20, 50));

		gameObject exit(0, Vector2f(100, 100), Vector2f(25, 25));
		exit.body.setFillColor(Color(Color::Blue));

		gameObject mapBounds(0, Vector2f(WINDOW_SIZE_X / 4, WINDOW_SIZE_Y / 4), Vector2f(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2));
		mapBounds.body.setFillColor(Color(50, 20, 20));

		objects1.push_back(outerBounds);
		objects1.push_back(exit);
		objects1.push_back(mapBounds);


		for (short int i = 0; i < 10; i++)
		{
			gameObject obj(0, Vector2f(100 + 60 * i, 50), Vector2f(20, 20));
			objects1.push_back(obj);
		}

		for (short int i = 0; i < 10; i++)
		{
			gameObject obj(0, Vector2f(30, 200 + i * 30), Vector2f(5, 5),false,Color::Black,Color::Green);
			objects1.push_back(obj);
		}

		for (short int i = 0; i < 5; i++)
		{
			gameObject obj(0, Vector2f(30 + i * 20, 200), Vector2f(5, 5), false, Color::Black, Color::Green);
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

}