#pragma once
#include "gameObject.h"
#include <vector>
#include <fstream>

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

		gameObject outerBounds(Vector2f(outline, outline), Vector2f(WINDOW_SIZE_X - 2 * outline, WINDOW_SIZE_Y - 2 * outline));
		outerBounds.body.setFillColor(Color(20,20,50));

		gameObject exit(Vector2f(20, 50), Vector2f(25, 25));
		exit.body.setFillColor(Color(Color::Blue));

		gameObject att(Vector2f(350, 250), Vector2f(20, 20), NULL, 50);

		objects0.push_back(outerBounds);
		objects0.push_back(exit);
		objects0.push_back(att);

		for (int i = 0; i < 3; i++)
		{
			gameObject obj(Vector2f(300 + rand() % 300, 300 + rand() % 300), Vector2f(rand() % 20, rand() % 20));
			obj.body.setFillColor(Color(20 * i, 30 * i, 50 * i));
			objects0.push_back(obj);
		}
		
		return objects0;
	}
	case 1:
	{
		ifstream input("D:/All mine/Game/Maindo/map1.txt");
		if (!input.is_open())
			cout << "VERY BAD";
		
		vector<gameObject> objects1;

		for (int i = 0; i < 3; i++)
		{
			if (char(input.peek()) == '#')
			{
				input.ignore(250, '\n');
				continue;
			}
			char* buf = new char[10];
			Vector2f position;
			input.getline(buf, 4, ',');
			position.x = atoi(buf);
			input.getline(buf, 4, ',');
			position.y = atoi(buf);

			Vector2f size;
			input.getline(buf, 4, ',');
			size.x = atoi(buf);
			input.getline(buf, 4, ';');
			size.y = atoi(buf);

			input.getline(buf, 1);

			gameObject obj(position, size);
			objects1.push_back(obj);
		}

		objects1.at(0).body.setFillColor(Color(20, 20, 50));

		objects1.at(1).body.setFillColor(Color::Blue);

		objects1.at(2).body.setFillColor(Color(50, 20, 20));

		for (short int i = 0; i < 10; i++)
		{
			gameObject obj(Vector2f(100 + 60 * i, 50), Vector2f(20, 20));
			objects1.push_back(obj);
		}

		for (short int i = 0; i < 10; i++)
		{
			gameObject obj(Vector2f(30, 200 + i * 30), Vector2f(5, 5), NULL, 0, 0, Color::Black,Color::Green);
			objects1.push_back(obj);
		}

		for (short int i = 0; i < 5; i++)
		{
			gameObject obj(Vector2f(30 + i * 20, 200), Vector2f(5, 5), NULL, 0, 0, Color::Black, Color::Green);
			objects1.push_back(obj);
		}
		input.close();
		return objects1;
	}
		default:
	{
			vector<T> objects_empty;
			return objects_empty;
	}

	}

}