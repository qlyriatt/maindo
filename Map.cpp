#include "Map.h"


void initialize(int map_type, vector<gameObject>& objects, vector<Entity>& entities, const vector<Texture>& textures)
{
	switch (map_type)
	{
	case 0:
	{
		float outline = 4;

		gameObject outerBounds(Vector2f(outline, outline), Vector2f(800 - 2 * outline, 600 - 2 * outline));
		outerBounds.body.setFillColor(Color(20, 20, 50));

		gameObject exit(Vector2f(20, 50), Vector2f(25, 25));
		exit.body.setFillColor(Color(Color::Blue));
		exit.interactionType = 1;

		objects.push_back(outerBounds);
		objects.push_back(exit);

		for (int i = 0; i < 3; i++)
		{
			gameObject obj(Vector2f(300 + rand() % 300, 300 + rand() % 300), Vector2f(rand() % 20, rand() % 20));
			obj.body.setFillColor(Color(20 * i, 30 * i, 50 * i));
			objects.push_back(obj);
		}


		//Entity a(0, Vector2f(350, 250), Vector2f(20, 20), NULL, 50);
		//Entity b(0, Vector2f(450, 350), Vector2f(15, 15), NULL, 75);

		//Weapon rifle(2, 600, 400, 30, &textures.at(1), 5);
		//Weapon pistol(1, 200, 200, 15, &textures.at(2), 3);
		//a.weapon = rifle;
		//b.weapon = rifle;

		//entities.push_back(a);
		//entities.push_back(b);

		break;
	}
	case 1:
	{
		ifstream input(DIRECTORY + "Txt/map1.txt");
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
			objects.push_back(obj);
		}

		objects.at(0).body.setFillColor(Color(20, 20, 50));

		objects.at(1).body.setFillColor(Color::Blue);

		objects.at(2).body.setFillColor(Color(50, 20, 20));

		for (short int i = 0; i < 10; i++)
		{
			gameObject obj(Vector2f(100 + 60 * i, 50), Vector2f(20, 20));
			objects.push_back(obj);
		}

		for (short int i = 0; i < 10; i++)
		{
			gameObject obj{ Vector2f(30, 200 + i * 30), Vector2f(5,5) };
			objects.push_back(obj);
		}

		for (short int i = 0; i < 5; i++)
		{
			gameObject obj{ Vector2f(30 + i * 20, 200), Vector2f(5, 5) };
			obj.body.setFillColor(Color::Green);
			objects.push_back(obj);
		}

		for (int i = 0; i < 6; i++)
		{
			gameObject obj(Vector2f(250 + 50 * i, 500), Vector2f(15, 15));
			obj.allowCollision = true;
			obj.ID = 1;
			obj.body.setFillColor(Color::Blue);
			obj.interactionType = 1;
			objects.push_back(obj);
		}

		for (int i = 0; i < 6; i++)
		{
			gameObject obj(Vector2f(250 + 50 * i, 550), Vector2f(15, 15));
			obj.allowCollision = true;
			obj.ID = 2;
			obj.body.setFillColor(Color::Yellow);
			obj.interactionType = 1;
			objects.push_back(obj);
		}

		input.close();
		break;
	}
	case 2:
	{
		gameObject roomTop({ 0,0 }, { 1920, 1080 * 2 });
		roomTop.allowCollision = true;
		roomTop.body.setFillColor(Color(120, 200, 30, 150));
		objects.push_back(roomTop);

		gameObject roomMiddle(roomTop.body.getPosition() + roomTop.body.getPoint(3), { 1920, 1080 * 1.5 });
		roomMiddle.allowCollision = true;
		roomMiddle.body.setFillColor(Color(200, 30, 120, 150));
		objects.push_back(roomMiddle);

		gameObject roomBottom(roomMiddle.body.getPosition() + roomMiddle.body.getPoint(3), { 1920 * 0.875, 1080 });
		roomBottom.allowCollision = true;
		roomBottom.body.setFillColor(Color(30, 30, 120, 150));
		objects.push_back(roomBottom);

		break;
	}

	}
}


void saveLevel(int currentLevel, const vector<gameObject>& objects, const vector<Entity>& entities, const vector<Texture>& textures)
{
	ofstream save(DIRECTORY + "Txt/level" + std::to_string(currentLevel) + "Save.txt");
	if (!save.is_open())
	{
		cout << "Unable to save the game" << endl;
		return;
	}


	save << currentLevel << endl;
	save << "########## Objects ##########" << endl;

	//---static properties that should be saved:
	// 
	// Shape body;
	//
	// bool	isDestroyable;
	// bool	isAnimated;
	// bool	allowCollision;
	// int	interactionType;
	// int	interactionTypeSpeciality;
	// 

	for (auto& i : objects)
	{
		save << i.body.getPosition().x << "," << i.body.getPosition().y << "," << i.body.getSize().x << "," << i.body.getSize().y << ",";

	}

	save.close();
}


void loadLevel(const int number, vector<gameObject>& objects)
{
	ifstream load;
	if (!load.is_open())
		cout << "very bad";

	bool levelFound = false;
	Vector2f position;
	Vector2f size;
	char buf[7];
	for (; !load.eof();)
	{
		load >> std::ws;
		if (char(load.peek()) == '#')
		{
			load.ignore(250, '\n');
			continue;
		}
		if (!levelFound)
		{
			load.get(buf, '\n');
			load.getline(buf, 10, '\n');
			//currentLevel = atoi(buf);
			levelFound = true;
			continue;
		}

		load.getline(buf, 7, ',');
		position.x = atoi(buf);
		load.getline(buf, 7, ',');
		position.y = atoi(buf);

		load.getline(buf, 7, ',');
		size.x = atoi(buf);
		load.getline(buf, 7, ';');
		size.y = atoi(buf);

		load.getline(buf, 7, '\n');

		objects.push_back(gameObject(position, size));
	}
}

