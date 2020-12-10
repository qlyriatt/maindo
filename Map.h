#pragma once
//#include "Player.h" ???
#include "Weapon.h"
#include "Entity.h"
#include <fstream>
using std::vector;
using std::ifstream;
using std::cout;

//lots of work waiting
void initialize(int map_type, vector<gameObject>* objects, vector<Entity>* entities, vector<Texture*>* textures)
{
	switch (map_type)
	{
	case 0:
	{
		float outline = 4;

		gameObject outerBounds(Vector2f(outline, outline), Vector2f(800 - 2 * outline, 600 - 2 * outline));
		outerBounds.body.setFillColor(Color(20,20,50));

		gameObject exit(Vector2f(20, 50), Vector2f(25, 25));
		exit.body.setFillColor(Color(Color::Blue));

		objects->push_back(outerBounds);
		objects->push_back(exit);

		for (int i = 0; i < 3; i++)
		{
			gameObject obj(Vector2f(300 + rand() % 300, 300 + rand() % 300), Vector2f(rand() % 20, rand() % 20));
			obj.body.setFillColor(Color(20 * i, 30 * i, 50 * i));
			objects->push_back(obj);
		}


		Entity a(0, Vector2f(350, 250), Vector2f(20, 20), NULL, 50);
		Entity b(0, Vector2f(450, 350), Vector2f(15, 15), NULL, 75);
		
		Weapon rifle(2, 600, 400, 30, textures->at(1), 5);
		Weapon pistol(1, 200, 200, 15, textures->at(2), 3);
		a.weapon = rifle;
		b.weapon = rifle;

		entities->push_back(a);
		entities->push_back(b);

		break;
	}
	case 1:
	{
		ifstream input("D:/All mine/Game/Maindo/map1.txt");
		if (!input.is_open())
			cout << "VERY BAD";
		
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
			objects->push_back(obj);
		}

		objects->at(0).body.setFillColor(Color(20, 20, 50));

		objects->at(1).body.setFillColor(Color::Blue);

		objects->at(2).body.setFillColor(Color(50, 20, 20));

		for (short int i = 0; i < 10; i++)
		{
			gameObject obj(Vector2f(100 + 60 * i, 50), Vector2f(20, 20));
			objects->push_back(obj);
		}

		for (short int i = 0; i < 10; i++)
		{
			gameObject obj(Vector2f(30, 200 + i * 30), Vector2f(5, 5), NULL, 0, 0, Color::Black,Color::Green);
			objects->push_back(obj);
		}

		for (short int i = 0; i < 5; i++)
		{
			gameObject obj(Vector2f(30 + i * 20, 200), Vector2f(5, 5), NULL, 0, 0, Color::Black, Color::Green);
			objects->push_back(obj);
		}

		for (int i = 0; i < 6; i++)
		{
			gameObject obj(Vector2f(250 + 50 * i, 500), Vector2f(15, 15));
			obj.allowCollision = true;
			obj.ID = 4;
			obj.interactionType = 1;
			objects->push_back(obj);
		}

		input.close();
		break;
	}

	}
}