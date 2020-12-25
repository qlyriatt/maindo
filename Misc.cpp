#include "Misc.h"


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
	names.push_back("Soretomo...	wa...ta...shi?");
	names.push_back("...'cause we'll be doing this till 6 in the morning"); //whoops
	names.push_back("Full sail ahead!");
	names.push_back("cout << vector.x << " " << vector.y << endl;");
	names.push_back("For $%@^$%^# sake, would you work already?");
	names.push_back("NULL");
	names.push_back("JOJO!-da-da-da-dum-dum-dum-dum-dum-GOLD WIND!");
	names.push_back("Bangarang!");
	names.push_back("This game is not suitable for children or those who are easily disturbed");
	names.push_back(" ");
	names.push_back("It's because the heart of mine has made it here before my body");
	names.push_back("Seven circles of OOP");
	names.push_back("Sleep is overrated");
	names.push_back("Number 15: Burger King foot lettuce");
	names.push_back("O - ya - su - mi");
	names.push_back("Back in the zenzenzense till this day been looking everywhere for you...");
	names.push_back("pickName()");
	names.push_back("Welcome back, Commander");
	names.push_back("Daijoubu da yo!");
	names.push_back("B7 flat 9 flat 13");
	names.push_back("I guess you guys aren't ready for that yet... but your kids are gonna love it");
	names.push_back("F - Fm - C");
	names.push_back("Microsoft C++ exception: std::length_error at memory location 0x0055BA50");
	names.push_back("Please be quiet");
	names.push_back("Error C2398: Element '1': conversion from 'int' to 'T' requires a narrowing conversion");
	names.push_back("Debug Assertion Failed!");
	names.push_back("Stretching and shrinking and stretching and shrinking");
	names.push_back("forward_list<Projectile> projectiles");
	names.push_back("----textures----textures----textures----textures----textures----textures----");
	names.push_back("git add --all");
	names.push_back("Premature optimization is the root of all evil");
	names.push_back("names.push_back(names.push_back(names.push_back(names.push_back(names.push_back(names.push_back('a'))))))");
	names.push_back("And they were roommates...");
	names.push_back("return names.at(rand() % names.size());");
	names.push_back("Paint.net is my best friend!");
	names.push_back("Tell me if I go straight on to morning / Would there be somebody there waiting for me?");
	names.push_back("If you can't understand it then it lies beyond your understanding");
	names.push_back("Citizens of Dalaran! Raise your eyes to the skies and observe!");
	names.push_back("All around the Stactus plant the stalker chased the bandit");
	names.push_back("Soap trusted you. I thought I could too.");
	names.push_back("Is it summertime already?");
	names.push_back("The fastest goodbye song");
	names.push_back("What's cookin' good lookin'?");


	return names.at(rand() % names.size());
}


float getTimeDiff(const Clock& clock, float time)
{
	return clock.getElapsedTime().asSeconds() - time;
}


int getCount(float storedTimeDifference, int animationStates, int changesPerSecondMultiplier)
{
	int count = storedTimeDifference * animationStates * changesPerSecondMultiplier;
	for (size_t i = 0; i < changesPerSecondMultiplier; i++)
	{
		count %= animationStates;
	}
	return count;
}


void alignTime(const float timestamp, const Clock& clock, Player& player, vector<gameObject>& objects, vector<Projectile>& projectiles)
{
	float elapsedTime = clock.getElapsedTime().asSeconds();

	for (auto& i : objects)
	{
		i.latestMoveUpdate = elapsedTime;
		i.latestAnimationUpdate = elapsedTime;
	}

	for (auto& i : projectiles)
	{
		i.latestMoveUpdate = elapsedTime;
		i.creationTime = elapsedTime - (timestamp - i.creationTime);
	}

	// aCT += eT 21 - lAU 20.5; count = 3; aCT += eT 48 - lAU 21(48); aCT += eT 48.5 - aCT 48; count = 4
	player.latestMoveUpdate = elapsedTime;
	player.latestAnimationUpdate = elapsedTime;
	player.weapon.latestShotTime = elapsedTime - (timestamp - player.weapon.latestShotTime);
}


void setOpacity(gameObjectStationary& object, int opacity)
{
	Color tmp = object.body.getFillColor();
	object.body.setFillColor(Color(tmp.r, tmp.g, tmp.b, opacity));
	tmp = object.body.getOutlineColor();
	object.body.setOutlineColor(Color(tmp.r, tmp.g, tmp.b, opacity));
}


void loadTexturesMenu(vector<Texture>& menuTextures)
{
	Texture menuLight;
	menuLight.loadFromFile(DIRECTORY + "Textures/menuLight.png");
	menuTextures.push_back(menuLight);

	Texture menuDark;
	menuDark.loadFromFile(DIRECTORY + "Textures/menuDark.png");
	menuTextures.push_back(menuDark);

	Texture menuButtonLight;
	menuButtonLight.loadFromFile(DIRECTORY + "Textures/menuButtonLight.png");
	menuTextures.push_back(menuButtonLight);

	Texture menuButtonDark;
	menuButtonDark.loadFromFile(DIRECTORY + "Textures/menuButtonDark.png");
	menuTextures.push_back(menuButtonDark);
}


void loadTexturesPause(vector<Texture>& pauseTextures)
{
	Texture menuLight;
	menuLight.loadFromFile(DIRECTORY + "Textures/pauseLight.png");
	pauseTextures.push_back(menuLight);

	Texture menuDark;
	menuDark.loadFromFile(DIRECTORY + "Textures/pauseDark.png");
	pauseTextures.push_back(menuDark);

	Texture menuButtonLight;
	menuButtonLight.loadFromFile(DIRECTORY + "Textures/pauseButtonLight.png");
	pauseTextures.push_back(menuButtonLight);

	Texture menuButtonDark;
	menuButtonDark.loadFromFile(DIRECTORY + "Textures/pauseButtonDark.png");
	pauseTextures.push_back(menuButtonDark);
}


void loadTextures(vector<Texture>& textures)
{
	Texture playerTexture;
	playerTexture.loadFromFile(DIRECTORY + "Textures/player.png");
	textures.push_back(playerTexture);

	Texture bulletPistolTexture;
	bulletPistolTexture.loadFromFile(DIRECTORY + "Textures/bulletPistol.png");
	textures.push_back(bulletPistolTexture);

	Texture bulletRifleTexture;
	bulletRifleTexture.loadFromFile(DIRECTORY + "Textures/bulletRifle.png");
	textures.push_back(bulletRifleTexture);
}


void finalDraw(RenderTexture& renderTexture, const vector<gameObject>& objects, const vector<Entity>& entities, const vector<Projectile>& projectiles,
	const Player& player)
{
	FloatRect viewField(renderTexture.getView().getCenter() - renderTexture.getView().getSize() / 2.f, renderTexture.getView().getSize());

	for (const auto& i : objects)
	{
		if (i.collisionCheck(viewField))
			renderTexture.draw(i.body);
	}

	for (const auto& i : entities)
	{
		if (i.collisionCheck(viewField))
			renderTexture.draw(i.body);
	}

	// fix later
	for (auto i : projectiles)
	{
		if (i.collisionCheck(viewField))
		{
			if (i.isMelee and DEBUG_LEVEL)
				i.body.setFillColor(Color(255, 255, 255, 150));
			renderTexture.draw(i.body);
		}
	}

	if (DEBUG_LEVEL)
	{
		RectangleShape tmp;
		tmp.setPosition(player.body.getPosition());
		tmp.setSize(player.body.getSize());
		tmp.setFillColor(Color(255, 0, 0, 150));
		renderTexture.draw(tmp);
		tmp.setPosition(player.sprite.getPosition());
		tmp.setSize(Vector2f(player.sprite.getGlobalBounds().width, player.sprite.getGlobalBounds().height));
		tmp.setFillColor(Color(0, 255, 0, 70));
		renderTexture.draw(tmp);
	}

	renderTexture.draw(player.sprite);
	renderTexture.display();
}


void finalDrawMinimap(RenderTexture& renderTexture, vector<gameObject>& objects, vector<Entity>& entities,
	vector<Projectile>& projectiles, Player& player)
{
	renderTexture.clear(Color::Transparent);

	for (auto& i : objects)
	{
		setOpacity(i, 200);
		renderTexture.draw(i.body);
		setOpacity(i);
	}

	for (auto& i : entities)
	{
		setOpacity(i, 200);
		renderTexture.draw(i.body);
		setOpacity(i);
	}

	for (auto& i : projectiles)
	{
		setOpacity(i, 200);
		renderTexture.draw(i.body);
		setOpacity(i);
	}

	setOpacity(player, 150);
	renderTexture.draw(player.sprite);
	setOpacity(player);
	renderTexture.display();
}


void levelLoad(RenderWindow& window, vector<gameObject>& objects, vector<Entity>& entities, int& currentLevel, int switchToLevel, const vector<Texture>& textures)
{
	Clock clock;

	RectangleShape loadScreen;
	loadScreen.setSize(Vector2f(window.getSize()));
	loadScreen.setFillColor(Color(Color::Black));
	window.draw(loadScreen);
	window.display();

	objects.erase(objects.begin(), objects.end());
	entities.erase(entities.begin(), entities.end());
	initialize(switchToLevel, objects, entities, textures);
	currentLevel = switchToLevel;

	for (; floor(clock.getElapsedTime().asSeconds() * 2) < 2;); //wait
	window.clear();
}


void cameraCollision(const gameObject& area, View& camera, const Player& player, const Vector2f WINDOW_SIZE)
{
	camera.setCenter(player.getCenter());
	const FloatRect allowedCameraArea = area.body.getGlobalBounds();
	const Vector2f cameraPosition = camera.getCenter() - camera.getSize() / 2.f;

	bool TL = allowedCameraArea.contains(cameraPosition);
	bool TR = allowedCameraArea.contains(cameraPosition + Vector2f(camera.getSize().x, 0));
	bool BL = allowedCameraArea.contains(cameraPosition + Vector2f(0, camera.getSize().y));
	bool BR = allowedCameraArea.contains(cameraPosition + camera.getSize());

	if (!(TL and TR and BL and BR))
	{
		if (TL)
		{
			if (BL)
				camera.setCenter(Vector2f(WINDOW_SIZE.x - camera.getSize().x / 2, player.getCenter().y));
			else if (TR)
				camera.setCenter(Vector2f(player.getCenter().x, WINDOW_SIZE.y - camera.getSize().y / 2));
			else
				camera.setCenter(WINDOW_SIZE - camera.getSize() / 2.f);
		}

		else if (BR)
		{
			if (TR)
				camera.setCenter(Vector2f(camera.getSize().x / 2, player.getCenter().y));
			else if (BL)
				camera.setCenter(Vector2f(player.getCenter().x, camera.getSize().y / 2));
			else
				camera.setCenter(camera.getSize() / 2.f);
		}

		else if (BL)
			camera.setCenter(Vector2f(WINDOW_SIZE.x - camera.getSize().x / 2, camera.getSize().y / 2));
		else if (TR)
			camera.setCenter(Vector2f(camera.getSize().x / 2, WINDOW_SIZE.y - camera.getSize().y / 2));
		else
			camera.setCenter(player.getCenter()); // precaution
	}
}


bool menuNavigation(const Event& event, const Vector2u& gridDimensions, int& count)
{
	const auto columns = gridDimensions.x;
	const auto rows = gridDimensions.y;

	if (event.key.code == Keyboard::W)
	{
		if (count < columns)
			count += columns * (rows - 1);
		else
			count -= columns;
		return true;
	}
	else if (event.key.code == Keyboard::S)
	{
		if (count > columns * (rows - 1) - 1)
			count -= columns * (rows - 1);
		else
			count += columns;
		return true;
	}
	else if (event.key.code == Keyboard::A)
	{
		if (count % columns == 0)
			count += columns - 1;
		else
			count--;
		return true;
	}
	else if (event.key.code == Keyboard::D)
	{
		if (count % columns == columns - 1)
			count -= columns - 1;
		else
			count++;
		return true;
	}

	return false;
}


vector<Vector2f> constructGrid(const Vector2u& gridDimensions, const Vector2u& textureSize, const Vector2u& renderTargetSize,
	const Vector2f& alignmentFactor, const Vector2f& cellOffsetFactor)
{
	//every Vector2<> is made float to overcome all the stupid warnings and errors that are caused by conversions and etc.

	//check for zeroes in gridDimensions
	//NOTE : 0 value is trasformed into 1 here for convenience
	const auto rows = gridDimensions.y == 0 ? 1 : gridDimensions.y;
	const auto columns = gridDimensions.x == 0 ? 1 : gridDimensions.x;

	//calculate alignment on renderTarget
	const Vector2f targetSize = Vector2f{ renderTargetSize };
	const Vector2f alignmentCenter = targetSize * alignmentFactor;

	//get sprite size 
	const Vector2f spriteSize = Vector2f{ textureSize };

	//calculate gap between sprites
	const Vector2f spriteGap = cellOffsetFactor == Vector2f{ 0, 0 } ? Vector2f{ 15, 15 } : spriteSize * cellOffsetFactor;

	//find the edge point 
	const float offsetEdgeX = spriteSize.x * columns / 2 + spriteGap.x * (columns - 1) / 2;
	const float offsetEdgeY = spriteSize.y * rows / 2 + spriteGap.y * (rows - 1) / 2;
	const Vector2f edgePoint = alignmentCenter - Vector2f{ offsetEdgeX, offsetEdgeY };

	//calculate final offset
	const Vector2f finalOffset = spriteSize + spriteGap;


	vector<Vector2f> gridVectors;
	gridVectors.reserve(rows * columns);

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < columns; j++)
		{
			gridVectors.push_back({ edgePoint + Vector2f{finalOffset.x * j, finalOffset.y * i} });
		}
	}

	return gridVectors;
}


void drawMenu(RenderWindow& window, const vector<Texture>& menuTextures, const Font& menuFont, const Vector2u& menuGrid,
	const int chosenButton, const Clock& clock, float& storedTime, float& latestAnimationUpdate, bool& isFirstDraw)
{
	const size_t lightUpTime = 3;


	window.clear();

	RenderTexture nativeResolutionBuffer;
	nativeResolutionBuffer.create(NATIVE_RESOLUTION.x, NATIVE_RESOLUTION.y);

	vector<Sprite> sprites;
	vector<Text> texts;

	Sprite background(menuTextures.at(1));
	sprites.push_back(background);

	Text text[]{ {"Continue", menuFont}, {"New Game", menuFont}, {"Whatever", menuFont}, {"Quit", menuFont} };
	size_t count = 0;
	for (auto& i : constructGrid(menuGrid, menuTextures.at(2).getSize(), nativeResolutionBuffer.getSize(), { 0.5, 0.6 }))
	{
		Sprite button(count == chosenButton ? menuTextures.at(2) : menuTextures.at(3));
		button.setPosition(i);
		sprites.push_back(button);

		text[count].setFillColor(Color::Black);
		text[count].setOutlineColor(count == chosenButton ? Color(175, 58, 210) : Color(112, 37, 135));
		text[count].setOutlineThickness(2);
		text[count].setCharacterSize(button.getGlobalBounds().height / 2);

		float textOffsetX = (button.getGlobalBounds().width - text[count].getGlobalBounds().width) / 2;
		float textOffsetY = (button.getGlobalBounds().height - text[count].getCharacterSize()) / 2;
		Vector2f textPosition = i + Vector2f{ textOffsetX, textOffsetY };
		text[count].setPosition(textPosition);
		texts.push_back(text[count]);

		count++;
	}

	for (auto& i : sprites)
		nativeResolutionBuffer.draw(i);

	for (auto& i : texts)
		nativeResolutionBuffer.draw(i);

	if (isFirstDraw)
	{
		RectangleShape tint;
		tint.setSize(Vector2f{ nativeResolutionBuffer.getSize() });
		if (storedTime < lightUpTime)
		{
			tint.setFillColor(Color(0, 0, 0, 255 * (1 - storedTime / lightUpTime)));
			nativeResolutionBuffer.draw(tint);
			storedTime += clock.getElapsedTime().asSeconds() - latestAnimationUpdate;
			latestAnimationUpdate = clock.getElapsedTime().asSeconds();
		}
		else
		{
			isFirstDraw = false;
			storedTime = latestAnimationUpdate = 0;
		}
	}

	nativeResolutionBuffer.display();
	Sprite finalOutput(nativeResolutionBuffer.getTexture());

	//SCALE DOWN FOR RESOLUTIONS LOWER THAN 1920/1080
	if (SHRINK_FACTOR != Vector2f{ 1, 1 })
		finalOutput.setScale(SHRINK_FACTOR);


	window.draw(finalOutput);
	window.display();
}


int showScreenMenu(RenderWindow& window, const vector<Texture>& menuTextures, const Font& menuFont)
{
	const Vector2u menuGrid = { 1, 4 };

	//tech stuff
	bool isFirstDraw = true;
	bool entryAnimationFinished = false;
	bool redraw = true;
	int chosenButton = 0;
	float storedTime = 0;
	float latestAnimationUpdate = 0;
	Event event;
	Clock clock;

	while (true)
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::E)
				{
					if (chosenButton == 0)
						return 0;
					else if (chosenButton == 1)
						return 2;
					//else if (chosenButton == 2)
					else if (chosenButton == menuGrid.y - 1)
						return -1;
				}

				else menuNavigation(event, menuGrid, chosenButton);
				redraw = true;
			}

			else if (event.type == Event::Closed)
			{
				window.close();
				return -1;
			}

			else if (event.type == Event::Resized)
			{
				//SHRINK_FACTOR = window.getSize() / NATIVE_RESOLUTION;
				redraw = true;
			}
		}

		if (redraw or isFirstDraw)
		{
			drawMenu(window, menuTextures, menuFont, menuGrid, chosenButton, clock, storedTime, latestAnimationUpdate, isFirstDraw);
			redraw = false;
		}
	}
}


void drawPause(RenderWindow& window, const vector<Texture>& pauseTextures, const Font& pauseFont, const Vector2u& pauseGrid,
	const int chosenButton)
{
	window.clear();

	RenderTexture nativeResolutionBuffer;
	nativeResolutionBuffer.create(NATIVE_RESOLUTION.x, NATIVE_RESOLUTION.y);

	vector<Sprite> sprites;
	vector<Text> texts;

	Sprite background(pauseTextures.at(1));
	sprites.push_back(background);

	Text text[]{ {"Continue", pauseFont}, {"Save game", pauseFont}, {"Whatever", pauseFont}, {"Quit to menu", pauseFont} };
	size_t count = 0;
	for (auto& i : constructGrid(pauseGrid, pauseTextures.at(2).getSize(), nativeResolutionBuffer.getSize(), { 0.5, 0.6 }))
	{
		Sprite button(count == chosenButton ? pauseTextures.at(2) : pauseTextures.at(3));
		button.setPosition(i);
		sprites.push_back(button);

		if (count < sizeof(text) / sizeof(Text)) //precaution
		{
			text[count].setFillColor(Color::Black);
			text[count].setOutlineColor(count == chosenButton ? Color(77, 193, 193) : Color(82, 119, 119));
			text[count].setOutlineThickness(2);
			text[count].setCharacterSize(button.getGlobalBounds().height / 2);

			float textOffsetX = (button.getGlobalBounds().width - text[count].getGlobalBounds().width) / 2;
			float textOffsetY = (button.getGlobalBounds().height - text[count].getCharacterSize()) / 2;
			Vector2f textPosition = i + Vector2f{ textOffsetX, textOffsetY };
			text[count].setPosition(textPosition);
			texts.push_back(text[count]);
		}

		count++;
	}

	for (auto& i : sprites)
		nativeResolutionBuffer.draw(i);

	for (auto& i : texts)
		nativeResolutionBuffer.draw(i);

	nativeResolutionBuffer.display();
	Sprite finalOutput(nativeResolutionBuffer.getTexture());

	//SCALE DOWN FOR RESOLUTIONS LOWER THAN 1920/1080
	if (SHRINK_FACTOR != Vector2f{ 1, 1 })
		finalOutput.setScale(SHRINK_FACTOR);


	window.draw(finalOutput);
	window.display();
}


int showScreenPause(RenderWindow& window, const vector<Texture>& pauseTextures, const Font& pauseFont)
{
	const Vector2u pauseGrid = { 1, 4 };
	RenderTexture pauseTexture;
	pauseTexture.create(window.getSize().x, window.getSize().y);


	int chosenButton = 0;
	bool redraw = true;
	Event event;
	while (true)
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				return -1;
			}

			else if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Escape)
				{
					return 1;
				}
				else if (event.key.code == Keyboard::E)
				{
					if (chosenButton == 0)
						return 1;
					else if (chosenButton == 1)
						return 2;
					else if (chosenButton == pauseGrid.y - 1)
						return 0;
				}
				else
					menuNavigation(event, pauseGrid, chosenButton);

				redraw = true;
			}
		}

		if (redraw)
		{
			drawPause(window, pauseTextures, pauseFont, pauseGrid, chosenButton);
			redraw = false;
		}
	}
}


void drawInventory(RenderWindow& window, const RenderTexture& background,
	const vector<Texture>& inventoryTextures, const Font& inventoryFont, const Vector2u& inventoryGrid, const int chosenItem)
{
	window.clear();

	RenderTexture nativeResolutionBuffer;
	nativeResolutionBuffer.create(NATIVE_RESOLUTION.x, NATIVE_RESOLUTION.y);

	vector<Sprite> sprites;
	vector<Text> text;
	

	//
	//
	//DRAW HERE
	//
	//
	
	
	nativeResolutionBuffer.display();
	Sprite finalOutput(nativeResolutionBuffer.getTexture());

	//SCALE DOWN FOR RESOLUTIONS LOWER THAN 1920/1080
	if (SHRINK_FACTOR != Vector2f{ 1, 1 })
		finalOutput.setScale(SHRINK_FACTOR);

	window.draw(Sprite{ background.getTexture() });

	RectangleShape tint;
	tint.setSize(Vector2f{ window.getSize() });
	tint.setFillColor(Color{ 0, 0, 0, 170 });
	window.draw(tint);

	window.draw(finalOutput);
	window.display();
}


int showScreenInventory(RenderWindow& window, const RenderTexture& background, const vector<Texture>& inventoryTextures, const Font& inventoryFont, Player& player)
{
	const Vector2u inventoryGrid = { 4,2 };

	bool redraw = true;
	int chosenItem = 0;
	Event event;

	while (true)
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Escape or event.key.code == Keyboard::I)
				{
					return 0;
				}
				//if this returns false, KR event does not satisfy any contitions so it is dismissed and redraw is not needed
				else if (!menuNavigation(event, inventoryGrid, chosenItem)) continue;

				redraw = true;
			}

			else if (event.type == Event::Closed)
			{
				window.close();
				return -1;
			}
		}

		if (redraw)
		{
			drawInventory(window, background, inventoryTextures, inventoryFont, inventoryGrid, chosenItem);
			redraw = false;
		}
	}
}


void applyPlayerInput(Player& player, vector<Projectile>& projectiles, const Clock& mainClock)
{
	player.upPressed = (Keyboard::isKeyPressed(Keyboard::W) ? true : false);
	player.rightPressed = (Keyboard::isKeyPressed(Keyboard::D) ? true : false);
	player.downPressed = (Keyboard::isKeyPressed(Keyboard::S) ? true : false);
	player.leftPressed = (Keyboard::isKeyPressed(Keyboard::A) ? true : false);
	player.leftShiftPressed = (Keyboard::isKeyPressed(Keyboard::LShift) ? true : false);

	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		player.weapon.action(projectiles, player, mainClock);
		//if (player.weapon.isMelee and !(getTimeDiff(mainClock, player.weapon.latestShotTime) > player.weapon.projectileLifetime))
		//	player.isUsingWeapon = true; //false?
	}
}


void projectileHandlerMain(const Clock& mainClock, vector<Projectile>& projectiles, vector<gameObject>& objects, Player& player, float& testTime)
{
	Clock testClock;
	// remove melee HB with expired swing or ranged projectiles with exceeding distance
	// before anything else
	projectiles.erase(remove_if(projectiles.begin(), projectiles.end(), [mainClock](const Projectile& projectile)
		{ return projectile.isMelee and getTimeDiff(mainClock, projectile.creationTime) > projectile.lifeTime ? true :
		!projectile.isMelee and projectile.traveledDistance > projectile.range ? true : false; }), projectiles.end());

	for (size_t i = 0; i < projectiles.size(); i++)
	{
		//MELEE
		if (projectiles.at(i).isMelee)
		{
			projectiles.at(i).body.setPosition(player.body.getPosition() + projectiles.at(i).swingHandle(mainClock));

			//check collisions
			for (size_t j = 1; j < objects.size(); j++)
			{
				if (projectiles.at(i).collisionCheck(objects.at(j)) and objects.at(j).isDestroyable and projectiles.at(i).penetration)
				{
					projectiles.at(i).penetration--;
					objects.erase(objects.begin() + j);
					j--;
				}
			}
		}
		//RANGED
		else
		{
			projectiles.at(i).updatePosition(mainClock.getElapsedTime().asSeconds());
			projectiles.at(i).traveledDistance += projectiles.at(i).latestDistanceCovered;

			//check collisions
			for (size_t j = 1; j < objects.size(); j++)
			{
				if (projectiles.at(i).collisionCheck(objects.at(j)))
				{
					if (objects.at(j).isDestroyable)
					{
						objects.erase(objects.begin() + j);
						j--;

						if (projectiles.at(i).penetration)
						{
							projectiles.at(i).penetration--;
							continue; //continue checking collisions for the same projectile
						}
					}

					projectiles.erase(projectiles.begin() + i);
					i--;
					break;
				}
			}
		}
	}
	player.weapon.reloadHandle(mainClock);
	testTime += testClock.getElapsedTime().asSeconds();
}


void objectHandlerMain(RenderWindow& window, vector<gameObjectStationary>& walls, vector<gameObject> objects, Player& player)
{
	bool interactionMessageDisplayed = false;
	bool needOverride = false;
	
	for (size_t i = 0; i < walls.size(); i++)
	{
		if (player.collisionCheck(walls.at(i), needOverride))
		{
			if (!walls.at(i).interactionType)
				continue;
			//otherwise collision and interaction ability are both present, handle them
		}
		else if (walls.at(i).interactionType)
		{
			if (!player.interactionCheck(walls.at(i)))
				continue;
			//otherwise interaction ability and interaction zone collision are both present, handle them
		}


		//if both conditions are not satisfied 
		//handle interactable gOS options
		if (player.interactionFlag)
		{
			//
			//interaction with gOS should be HERE
			//
			player.interactionFlag = false;
		}
		else if (!interactionMessageDisplayed)
		{
			//
			//interaction message display should be HERE
			//
			interactionMessageDisplayed = true;
		}
	}

	//gameObject handler
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (player.collisionCheck(objects.at(i), needOverride))
		{
			if (!objects.at(i).interactionType)
				continue;
			//otherwise collision and interaction ability are both present, handle them
		}
		else if (objects.at(i).interactionType)
		{
			if (!player.interactionCheck(objects.at(i)))
				continue;
			//otherwise interaction ability and interaction zone collision are both present, handle them
		}


		//if both conditions are not satisfied 
		//handle interactable gO options
		if (player.interactionFlag)
		{
			//
			//interaction with gO should be HERE
			//
			// EXAMPLE: 
			if (objects.at(i).body.getFillColor() == Color::Green)
				objects.at(i).body.setFillColor(Color::Black);
			else
				objects.at(i).body.setFillColor(Color::Green);
			//
			//
			player.interactionFlag = false;
		}
		else if (!interactionMessageDisplayed)
		{
			//
			//interaction message display should be HERE
			//
			// EXAMPLE: 
			RectangleShape msg;
			msg.setSize(Vector2f(20, 5));
			msg.setPosition(Vector2f(player.body.getPosition() + Vector2f(0, -10)));
			msg.setFillColor(Color(Color::White));
			window.draw(msg);
			//
			//
			interactionMessageDisplayed = true;
		}
	}
	if (!needOverride)
		player.overrideInputX = player.overrideInputY = false;
}
