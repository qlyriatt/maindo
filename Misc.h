#pragma once
#include "Player.h"
#include "Map.h"
#include <time.h>
using std::vector;
using std::cout;
using std::endl;

extern const std::string DIRECTORY;
//const Vector2f WINDOW_SIZE{ 1920, 1080 };
const Vector2f WINDOW_SIZE{ 1366, 768 };
//const Vector2f CAMERA_SIZE{ 1920, 1080 };
const Vector2f CAMERA_SIZE{ 1366, 768 };
const Vector2f INVENTORY_SIZE{ CAMERA_SIZE / 2.f };
const Vector2u NATIVE_RESOLUTION = { 1920, 1080 };
Vector2f SHRINK_FACTOR = { WINDOW_SIZE.x / 1920, WINDOW_SIZE.y / 1080 };

#define DEBUG_LEVEL 1



//pls help
namespace sf
{
	template<typename T, typename U>
	Vector2f operator *(const Vector2<T>& left, const Vector2<U>& right)
	{
		return Vector2f(left.x * right.x, left.y * right.y);
	}

	template<typename T>
	Vector2<T> operator *(const Vector2<T>& left, const Vector2<T>& right)
	{
		return Vector2<T>(left.x * right.x, left.y * right.y);
	}

	template<typename T, typename U>
	Vector2f operator /(const Vector2<T>& left, const Vector2<U>& right)
	{
		return Vector2f(float(left.x) / float(right.x), float(left.y) / float(right.y));
	}
};




//every possible use(less)(ful) function that can be thought of

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
	names.push_back("Oyasumi");
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

	return names.at(rand() % names.size());
}


float getTimeDiff(const Clock& clock, float time)
{
	return clock.getElapsedTime().asSeconds() - time;
}


int getCount(float storedTimeDifference, int animationStates, int changesPerSecondMultiplier = 1)
{
	int count = storedTimeDifference * animationStates * changesPerSecondMultiplier;
	for (size_t i = 0; i < changesPerSecondMultiplier; i++)
	{
		count %= animationStates;
	}
	return count;
}


//aligns latestTimeUpdate (or else) for everything after additional rendering
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


/////////////////////////////////////////////////
/// @brief Changes opacity of an object
/// @param object Target
/// @param opacity Opacity to set, default is non-transparent
/////////////////////////////////////////////////
void setOpacity(gameObjectStationary& object, int opacity = 255)
{
	Color tmp = object.body.getFillColor();
	object.body.setFillColor(Color(tmp.r, tmp.g, tmp.b, opacity));
	tmp = object.body.getOutlineColor();
	object.body.setOutlineColor(Color(tmp.r, tmp.g, tmp.b, opacity));
}


void loadTexturesMenu(vector<Texture>& texturesMenu)
{
	Texture menuLight;
	menuLight.loadFromFile(DIRECTORY + "Textures/menuLight.png");
	texturesMenu.push_back(menuLight);

	Texture menuDark;
	menuDark.loadFromFile(DIRECTORY + "Textures/menuDark.png");
	texturesMenu.push_back(menuDark);

	Texture menuButtonLight;
	menuButtonLight.loadFromFile(DIRECTORY + "Textures/menuButtonLight.png");
	texturesMenu.push_back(menuButtonLight);

	Texture menuButtonDark;
	menuButtonDark.loadFromFile(DIRECTORY + "Textures/menuButtonDark.png");
	texturesMenu.push_back(menuButtonDark);
}


void loadTexturesPause(vector<Texture>& texturesPause)
{
	Texture menuLight;
	menuLight.loadFromFile(DIRECTORY + "Textures/pauseLight.png");
	texturesPause.push_back(menuLight);

	Texture menuDark;
	menuDark.loadFromFile(DIRECTORY + "Textures/pauseDark.png");
	texturesPause.push_back(menuDark);

	Texture menuButtonLight;
	menuButtonLight.loadFromFile(DIRECTORY + "Textures/pauseButtonLight.png");
	texturesPause.push_back(menuButtonLight);

	Texture menuButtonDark;
	menuButtonDark.loadFromFile(DIRECTORY + "Textures/pauseButtonDark.png");
	texturesPause.push_back(menuButtonDark);
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


/////////////////////////////////////////////////
/// @brief Draws everything in the current frame
/// @param renderTexture RenderTexture to draw to
/////////////////////////////////////////////////
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


/////////////////////////////////////////////////
/// @brief Simple function to navigate any menu 
/// NOTE : count should be a non-const reference
/// @param event Event to handle
/// @param gridDimensions Menu grid dimensions (X = rows, Y = columns)
/// @param count Reference to current menu count (button, item, etc.)
/// @returns True if event was handled succesfully, false otherwise
/////////////////////////////////////////////////
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


/////////////////////////////////////////////////
/// @brief Draws an additional texture layer
/// @param	targetTexture RenderTexture to draw to
/// @param	spritesToRender Objects to draw to targetTexture
/// @param  pendingDraw Texture that should be behind what is going to be rendered
/// @return Sprite ready for display
/////////////////////////////////////////////////
Sprite additionalLayerRendering(RenderTexture& targetTexture, const vector<Sprite>& spritesToRender)
{
	targetTexture.clear();

	for (auto& i : spritesToRender)
	{
		targetTexture.draw(i);
	}

	targetTexture.display();

	return Sprite(targetTexture.getTexture());
}


/////////////////////////////////////////////////
/// @brief Overload that draws an additional texture layer on top of other texture
/// @param	targetTexture RenderTexture to draw to
/// @param	spritesToRender Objects to draw to targetTexture
/// @param  pendingDraw Texture that should be behind what is going to be rendered
/// @return Sprite ready for display
/////////////////////////////////////////////////
Sprite additionalLayerRendering(RenderTexture& targetTexture, const vector<Sprite>& spritesToRender, const RenderTexture& pendingDraw)
{
	targetTexture.clear();

	targetTexture.draw(Sprite(pendingDraw.getTexture())); //draw background

	for (auto& i : spritesToRender)	//draw the rest
	{
		targetTexture.draw(i);
	}

	targetTexture.display();
	
	return Sprite(targetTexture.getTexture());
}


/////////////////////////////////////////////////
/// @brief Constructs a rectangle grid of graphic vectors
/// @param cellCount Grid dimensions as X - columns and Y - rows. Either must be non-zero
/// @param gridSize Size of constructed grid
/// @param gridPosition Starting point of the grid
/// @param cellSize Size of the inside cell, base grid is divided instead if left default
/// @deprecated Actually it's deprecated since day 1
/// @return An array of vectors
/////////////////////////////////////////////////
const vector<Vector2f> constructRectangleGridVectors(const Vector2u cellCount, const Vector2u gridSize, 
	const Vector2u gridPosition = { 0,0 }, const Vector2u cellSize = { 0,0 })
{	
	//everything is proportional to the window size for now

	const size_t rows = cellCount.y;
	const size_t columns = cellCount.x;
	
	vector<Vector2f> gridVectors;
	gridVectors.reserve(rows * columns);

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < columns; j++)
		{
			Vector2f initialOffset = { Vector2f(gridPosition) + Vector2f(gridSize.x / columns * j, gridSize.y / rows * i) };
			
			if (cellSize == Vector2u{ 0,0 })
				gridVectors.push_back(initialOffset);
			else
			{
				Vector2f cellOffset = { (Vector2f(gridSize.x / columns, gridSize.y / rows) - Vector2f(cellSize)) / 2.f };
				gridVectors.push_back(initialOffset + cellOffset);
			}
		}
	}
	return gridVectors;
}


vector<RectangleShape> defineInventory(const Vector2u renderTargetSize, const Player& player, const Vector2u itemGrid,  const int chosenItem)
{
	//everything you can tweak to change inventory appearance
	const Vector2u INVENTORY_POSITION = renderTargetSize / size_t(4); 
	const Vector2u INVENTORY_SIZE = INVENTORY_POSITION * size_t(2);
	const Vector2u ITEM_SIZE = { 50,50 };

	vector<RectangleShape> objects;

	RectangleShape tintedScreen;
	tintedScreen.setSize(Vector2f(renderTargetSize));
	tintedScreen.setFillColor(Color(0, 0, 0, 140));
	objects.push_back(tintedScreen);

	RectangleShape inventoryShape;
	inventoryShape.setSize(Vector2f(INVENTORY_SIZE));
	inventoryShape.setPosition(Vector2f(INVENTORY_POSITION));
	inventoryShape.setFillColor(Color(255, 0, 0, 170));
	objects.push_back(inventoryShape);

	if (DEBUG_LEVEL)
	{
		for (auto& i : constructRectangleGridVectors(itemGrid, INVENTORY_SIZE, INVENTORY_POSITION))
		{
			RectangleShape obj;
			obj.setPosition(i);
			obj.setSize(Vector2f(INVENTORY_SIZE.x / itemGrid.x, INVENTORY_SIZE.y / itemGrid.y));
			obj.setFillColor(Color::Transparent);
			obj.setOutlineColor(Color(150, 150, 0, 200));
			obj.setOutlineThickness(3);
			objects.push_back(obj);
		}
	}

	size_t count = 0;
	for (auto& i : constructRectangleGridVectors(itemGrid, INVENTORY_SIZE, INVENTORY_POSITION, ITEM_SIZE))
	{
		RectangleShape obj;
		obj.setPosition(i);
		obj.setSize(Vector2f(ITEM_SIZE));
		if (count == chosenItem)
		{
			obj.setOutlineThickness(3);
			obj.setOutlineColor(Color::Green);
		}
		
		if (count < player.inventorySlots.size())
		{
			if (player.inventorySlots.at(count) == 1)
				obj.setFillColor(Color::Blue);
			else if (player.inventorySlots.at(count) == 2)
				obj.setFillColor(Color::Yellow);
			else
				obj.setFillColor(Color::Black);
		}

		objects.push_back(obj);
		count++;
	}

	return objects;
}


//void showScreenInventory(RenderWindow& window, const RenderTexture& mainGameTexture, Player& player)
//{
//	const Vector2u itemGrid = { 4,2 };
//	RenderTexture finalTexture;
//	finalTexture.create(window.getSize().x, window.getSize().y);
//
//
//	int chosenItem = 0;
//	bool redraw = true;
//	Event event;
//
//	while (true)
//	{
//		while (window.pollEvent(event))
//		{
//			if (event.type == Event::Closed)
//			{
//				window.close();
//				return;
//			}
//
//			else if (event.type == Event::KeyReleased)
//			{
//				if (event.key.code == Keyboard::I)
//				{
//					player.isInventoryOpen = false;
//					return;
//				}
//
//				//any interactions should be here
//				else if (event.key.code == Keyboard::E)
//				{
					//if (player.inventorySlots.at(chosenItem) == 1 and player.health < player.maxHealth)
					//{
					//	player.health += 20;
					//	player.inventorySlots.at(chosenItem) = 0;
					//}
					//else if (player.inventorySlots.at(chosenItem) == 2 and player.health > 0)
					//{
					//	player.health -= 20;
					//	player.inventorySlots.at(chosenItem) = 0;
					//}
					//else continue; //<---
//				}
//
//				else
//					menuNavigation(event, itemGrid, chosenItem);
//
//				redraw = true;	//redraw on chosen item change
//			}
//		}
//
//		if (redraw)
//		{
//			window.draw(additionalLayerRendering(finalTexture, defineInventory(window.getSize(), player, itemGrid, chosenItem), mainGameTexture));
//			window.display();
//			redraw = false;
//		}
//	}
//}


/////////////////////////////////////////////////
// Very (not)useful calculations that help solve the great (unexisting) problem of
// having to construct many grid-like sets of objects by making it ten millions times harder 
// than it actually is, and all thanks to standartisation and code reusage, 
// because making one function do anything for everything was a BRILLIANT IDEA!!!
/////////////////////////////////////////////////
vector<Vector2f> constructGrid(const Vector2u cellCount, const Texture& texture, const RenderTarget& renderTarget, 
	const Vector2f& alignmentFactor, const Vector2f& cellOffsetFactor = { 0, 0 })
{
	const auto rows = cellCount.y == 0 ? 1 : cellCount.y;
	const auto columns = cellCount.x == 0 ? 1 : cellCount.x;
	const Vector2f spriteSize = Vector2f{ texture.getSize() };
	const Vector2f targetSize = Vector2f{ renderTarget.getSize() };
	const Vector2f alignmentCenter = targetSize * alignmentFactor;
	const Vector2f spriteGap = cellOffsetFactor == Vector2f{ 0, 0 } ? Vector2f{ 15, 15 } : spriteSize * cellOffsetFactor;
	const float offsetEdgeX = spriteSize.x * columns / 2 + spriteGap.x * (columns - 1) / 2;
	const float offsetEdgeY = spriteSize.y * rows / 2 + spriteGap.y * (rows - 1) / 2;
	const Vector2f edgePoint = alignmentCenter - Vector2f{ offsetEdgeX, offsetEdgeY };
	const Vector2f finalOffset = spriteSize + spriteGap;
	//...hence fuck off

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



int showScreenMenu(RenderWindow& window)
{
	const Vector2u menuGrid = { 4,2 };
	RenderTexture menuTexture;
	menuTexture.create(window.getSize().x, window.getSize().y);

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
				if (event.key.code == Keyboard::E)
				{
					if (chosenButton == 0)
						return 1;
					else if (chosenButton == 1)
						return 2;
					else if (chosenButton == pauseGrid.y - 1)
						return 0;
				}
				else
					menuNavigation(event, menuGrid, chosenButton);

				redraw = true;
			}
		}
	}

}


//enum AdditionalExitCodes
//{
//	requireNavigation = -2,
//	windowClosed,
//};
//
//
//enum ScreenTypes
//{
//	menu = 0,
//	pause,
//	inventory
//};
//
//
//Vector2u getGridDimensions(const int screenType)
//{
//	switch (screenType)
//	{
//	case ScreenTypes::menu: return { 1,4 };
//	case ScreenTypes::pause: return { 1,4 };
//	case ScreenTypes::inventory: return { 4,2 };
//	default:
//		throw("getGridDimensions: NO SUCH SCREENTYPE");
//		return { 0,0 };
//	}
//}
//
//
//int additionalEventHandler(const int screenType, const Event& event, const Vector2u gridDimensions, int& chosenButton, 
//	void* const additionalData = nullptr)
//{
//	switch (screenType)
//	{
//	case ScreenTypes::menu:
//
//		if (event.type == Event::KeyReleased)
//		{
//			if (event.key.code == Keyboard::E)
//			{
//				if (chosenButton == 0)
//					return 0;
//				else if (chosenButton == 1)
//					return 2;
//				//else if (chosenButton == 2)
//				else if (chosenButton == 3)
//					return -1;
//			}
//		}
//		break;
//	case ScreenTypes::pause:
//
//		if (event.type == Event::KeyReleased)
//		{
//			if (event.key.code == Keyboard::Escape)
//				return 1;
//
//			else if (event.key.code == Keyboard::E)
//			{
//				if (chosenButton == 0)
//					return 1;
//				else if (chosenButton == 1)
//					return 2;
//				else if (chosenButton == 3)
//					return 0;
//			}
//		}
//		break;
//	case ScreenTypes::inventory:
//		
//		if (event.type == Event::KeyReleased)
//		{
//			if (event.key.code == Keyboard::I)
//				return 0;
//
//			//inventory interactions should be supported here
//			if (event.key.code == Keyboard::E)
//			{
//				if (!additionalData)
//					throw("additionalEventHandler: ADDITIONAL DATA --- NULL PTR");
//				Player* const player = static_cast<Player*>(additionalData);
//
//				if (player->inventorySlots.at(chosenButton) == 1 and player->health < player->maxHealth)
//				{
//					player->health += 20;
//					player->inventorySlots.at(chosenButton) = 0;
//				}
//				else if (player->inventorySlots.at(chosenButton) == 2 and player->health > 0)
//				{
//					player->health -= 20;
//					player->inventorySlots.at(chosenButton) = 0;
//				}
//			}
//		}
//		break;
//	default:
//
//		throw("additionalEventHandler: NO SUCH SCREENTYPE");
//	}
//
//	// if the event was not handled in specialized handler, 
//	// it may be navigational and require additional check
//	return AdditionalExitCodes::requireNavigation;
//}
//
//
//void additionalScreenDrawer(const int screenType, RenderWindow& window)
//{
//	window.clear();
//
//	RenderTexture nativeResolutionBuffer;
//	nativeResolutionBuffer.create(NATIVE_RESOLUTION.x, NATIVE_RESOLUTION.y);
//
//	window.display();
//}
//
//
//int showAdditionalScreen(const int screenType, RenderWindow& window, void* const additionalData = nullptr)
//{
//	using AEC = AdditionalExitCodes;
//
//	const Vector2u gridDimensions = getGridDimensions(screenType);
//
//
//	int chosenButton = 0;
//	bool redraw = true;
//	Event event;
//	while (true)
//	{
//		while (window.pollEvent(event))
//		{
//			//get closed window out of the way first
//			if (event.type == Event::Closed)
//			{
//				window.close();
//				return -1;
//			}
//
//			//call specialized handler
//			else 
//			{
//				switch (additionalEventHandler(screenType, event, gridDimensions, chosenButton, additionalData))
//				{
//				case AEC::requireNavigation:
//					if(!menuNavigation(event, gridDimensions, chosenButton)) continue; //if event is not handled by any conditions, go to the next one
//					break;
//				case AEC::windowClosed:
//					return -1;
//				}
//				redraw = true;
//			}
//		}
//		
//		if (redraw)
//		{
//			//draws directly to the window
//			additionalScreenDrawer(screenType, window);
//			redraw = false;
//		}
//	}
//}



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
	for (auto& i : constructGrid(pauseGrid, pauseTextures.at(2), nativeResolutionBuffer, { 0.5, 0.6 }))
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


/////////////////////////////////////////////////
/// @brief Internal function that draws menu elements to the window
///
/// @param window Window to draw to
/// @param menuTextures A vector of menu textures
/// @param menuGrid How much columns and rows are in the menu (Vector2u {columns, rows} )
/// @param menuFont Font to use with menu
/// @param chosenButton Current chosen button
/// @param clock Internal clock
/// @param storedTime Time storage for animation
/// @param latestAnimationUpdate Timestamp of latest animation update
/// @param isFirstDraw Does the menu require special intro animation
/////////////////////////////////////////////////
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
	for (auto& i : constructGrid(menuGrid, menuTextures.at(2), nativeResolutionBuffer, { 0.5, 0.6 }))
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


/////////////////////////////////////////////////
/// @brief Draws menu and allows menu interaction
///
/// @param window Main render window
/// @param menuTextures Textures used in menu drawing
/// @param menuFont Font used in menu drawing
/// 
/// @return -1 if the window was closed, 0 if level is loading from save, otherwise a level to load
/////////////////////////////////////////////////
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


void projectileHandlerMain(const Clock& mainClock, vector<Projectile>& projectiles, vector<gameObject>& objects, Player& player)
{
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
			projectiles.at(i).updatePosition(mainClock);
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
}