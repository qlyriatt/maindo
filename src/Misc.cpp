#include "Misc.h"
#pragma warning(push)
#pragma warning(disable : 4018 4244 4305)




int getCount(float storedTimeDifference, int animationStates, const size_t changesPerSecondMultiplier)
{
	int count = storedTimeDifference * animationStates * changesPerSecondMultiplier;
	for (size_t i = 0; i < changesPerSecondMultiplier; i++)
	{
		count %= animationStates;
	}
	return count;
}


// void alignTime(const float timestamp, const Clock& clock, Player& player, vector<gameObject>& objects, vector<Projectile>& projectiles)
// {
// 	float elapsedTime = clock.getElapsedTime().asSeconds();

// 	for (auto& i : objects)
// 	{
// 		i.latestMoveUpdate = elapsedTime;
// 		i.latestAnimationUpdate = elapsedTime;
// 	}

// 	for (auto& i : projectiles)
// 	{
// 		i.latestMoveUpdate = elapsedTime;
// 		i.creationTime = elapsedTime - (timestamp - i.creationTime);
// 	}

// 	// aCT += eT 21 - lAU 20.5; count = 3; aCT += eT 48 - lAU 21(48); aCT += eT 48.5 - aCT 48; count = 4
// 	player.latestMoveUpdate = elapsedTime;
// 	player.latestAnimationUpdate = elapsedTime;
// 	player.weapon.latestShotTime = elapsedTime - (timestamp - player.weapon.latestShotTime);
// }



// void finalDraw(RenderTexture& renderTexture, const vector<gameObject>& objects, const vector<Entity>& entities, const vector<Projectile>& projectiles,
// 	const Player& player)
// {
// 	FloatRect viewField(renderTexture.getView().getCenter() - renderTexture.getView().getSize() / 2.f, renderTexture.getView().getSize());

// 	for (const auto& i : objects)
// 	{
// 		if (i.collisionCheck(viewField))
// 			renderTexture.draw(i.body);
// 	}

// 	for (const auto& i : entities)
// 	{
// 		if (i.collisionCheck(viewField))
// 			renderTexture.draw(i.body);
// 	}

// 	// fix later
// 	for (auto i : projectiles)
// 	{
// 		if (i.collisionCheck(viewField))
// 		{
// 			if (i.isMelee and DEBUG_LEVEL)
// 				i.body.setFillColor(Color(255, 255, 255, 150));
// 			renderTexture.draw(i.body);
// 		}
// 	}

// 	if (DEBUG_LEVEL)
// 	{
// 		RectangleShape tmp;
// 		tmp.setPosition(player.body.getPosition());
// 		tmp.setSize(player.body.getSize());
// 		tmp.setFillColor(Color(255, 0, 0, 150));
// 		renderTexture.draw(tmp);
// 		tmp.setPosition(player.sprite.getPosition());
// 		tmp.setSize(Vector2f(player.sprite.getGlobalBounds().width, player.sprite.getGlobalBounds().height));
// 		tmp.setFillColor(Color(0, 255, 0, 70));
// 		renderTexture.draw(tmp);
// 	}

// 	renderTexture.draw(player.sprite);
// 	renderTexture.display();
// }


// void finalDrawMinimap(RenderTexture& renderTexture, vector<gameObject>& objects, vector<Entity>& entities,
// 	vector<Projectile>& projectiles, Player& player)
// {
// 	renderTexture.clear(Color::Transparent);

// 	for (auto& i : objects)
// 	{
// 		setOpacity(i, 200);
// 		renderTexture.draw(i.body);
// 		setOpacity(i);
// 	}

// 	for (auto& i : entities)
// 	{
// 		setOpacity(i, 200);
// 		renderTexture.draw(i.body);
// 		setOpacity(i);
// 	}

// 	for (auto& i : projectiles)
// 	{
// 		setOpacity(i, 200);
// 		renderTexture.draw(i.body);
// 		setOpacity(i);
// 	}

// 	setOpacity(player, 150);
// 	renderTexture.draw(player.sprite);
// 	setOpacity(player);
// 	renderTexture.display();
// }


// void levelLoad(RenderWindow& window, vector<gameObject>& objects, vector<Entity>& entities, int& currentLevel, int switchToLevel, const vector<Texture>& textures)
// {
// 	Clock clock;

// 	RectangleShape loadScreen;
// 	loadScreen.setSize(Vector2f(window.getSize()));
// 	loadScreen.setFillColor(Color(Color::Black));
// 	window.draw(loadScreen);
// 	window.display();

// 	objects.erase(objects.begin(), objects.end());
// 	entities.erase(entities.begin(), entities.end());
// 	initialize(switchToLevel, objects, entities, textures);
// 	currentLevel = switchToLevel;

// 	for (; floor(clock.getElapsedTime().asSeconds() * 2) < 2;); //wait
// 	window.clear();
// }


// void cameraCollision(const gameObject& area, View& camera, const Player& player, const Vector2f WINDOW_SIZE)
// {
// 	camera.setCenter(player.getCenter());
// 	const FloatRect allowedCameraArea = area.body.getGlobalBounds();
// 	const Vector2f cameraPosition = camera.getCenter() - camera.getSize() / 2.f;

// 	bool TL = allowedCameraArea.contains(cameraPosition);
// 	bool TR = allowedCameraArea.contains(cameraPosition + Vector2f(camera.getSize().x, 0));
// 	bool BL = allowedCameraArea.contains(cameraPosition + Vector2f(0, camera.getSize().y));
// 	bool BR = allowedCameraArea.contains(cameraPosition + camera.getSize());

// 	if (!(TL and TR and BL and BR))
// 	{
// 		if (TL)
// 		{
// 			if (BL)
// 				camera.setCenter(Vector2f(WINDOW_SIZE.x - camera.getSize().x / 2, player.getCenter().y));
// 			else if (TR)
// 				camera.setCenter(Vector2f(player.getCenter().x, WINDOW_SIZE.y - camera.getSize().y / 2));
// 			else
// 				camera.setCenter(WINDOW_SIZE - camera.getSize() / 2.f);
// 		}

// 		else if (BR)
// 		{
// 			if (TR)
// 				camera.setCenter(Vector2f(camera.getSize().x / 2, player.getCenter().y));
// 			else if (BL)
// 				camera.setCenter(Vector2f(player.getCenter().x, camera.getSize().y / 2));
// 			else
// 				camera.setCenter(camera.getSize() / 2.f);
// 		}

// 		else if (BL)
// 			camera.setCenter(Vector2f(WINDOW_SIZE.x - camera.getSize().x / 2, camera.getSize().y / 2));
// 		else if (TR)
// 			camera.setCenter(Vector2f(camera.getSize().x / 2, WINDOW_SIZE.y - camera.getSize().y / 2));
// 		else
// 			camera.setCenter(player.getCenter()); // precaution
// 	}
// }


bool gridEvent(const Event& event, int rows, int columns, int &current_row, int &current_column)
{
	// TODO: make way for non-wrapping navigation
	bool wrapping = true;

	// handle pressed key to navigate grid
	//
	// 	   	   columns
	//			0   1
	// r 	0	x	x	
	// o 	1	x	x
	// w 	2	x	x
	// s 	3	x	x
	//
	//

	if (event.key.code == Keyboard::W) // up
	{
		if (current_row == 0 && wrapping)
			current_row = rows - 1;
		else
			current_row -= 1;

		return true;
	}
	if (event.key.code == Keyboard::S) // down
	{
		if (current_row == rows - 1 && wrapping)
			current_row = 0;
		else
			current_row += 1;

		return true;
	}
	if (event.key.code == Keyboard::A) // left
	{
		if (!current_column && wrapping)
			current_column = columns - 1;
		else
			current_column -= 1;

		return true;
	}
	else if (event.key.code == Keyboard::D) // right
	{
		if (current_column == columns - 1 && wrapping)
			current_column = 0;
		else
			current_column += 1;
			
		return true;
	}

	return false;
}


vector<Vector2f> gridLayout(int rows, int columns, const Vector2u& cell_size, const Vector2u& target_size,
	const Vector2f& alignment_factor, const Vector2f& cell_gap_factor)
{
	const auto center = Vector2f(target_size) * alignment_factor;

	const auto cell_gap = cell_gap_factor == Vector2f(0, 0) ? Vector2f(15, 15) : cell_size * cell_gap_factor;

	double width = cell_size.x * columns / 2 + cell_gap.x * (columns - 1) / 2;
	double height = cell_size.y * rows / 2 + cell_gap.y * (rows - 1) / 2;
	const auto TL = center - Vector2f(width, height);

	const auto cell_offset = Vector2f(cell_size) + cell_gap;

	vector<Vector2f> grid;
	grid.reserve(rows * columns);
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < columns; ++col)
		{
			grid.push_back({TL + Vector2f(cell_offset.x * col, cell_offset.y * row)});
		}
	}

	return grid;
}

//FULLY DONE (HARDCODED)
void drawPause(RenderWindow& window, const vector<Texture>& pauseTextures, const Font& pauseFont, const Vector2u& pauseGrid,
	const Vector2u& chosenButton)
{
	window.clear();

	RenderTexture nativeResolutionBuffer;
	nativeResolutionBuffer.create(NATIVE_RESOLUTION.x, NATIVE_RESOLUTION.y);

	vector<Sprite> sprites;
	vector<Text> texts;

	// pause background
	Sprite background(pauseTextures.at(1));
	sprites.push_back(background);

	// pause menu buttons text
	vector<Text> text { {}, {"Continue", pauseFont}, {"Save game", pauseFont}, {"Whatever", pauseFont}, {"Quit to menu", pauseFont} };
	int count = 1;

	// create buttons
	// for (auto& i : constructGrid(pauseGrid, pauseTextures.at(2).getSize(), nativeResolutionBuffer.getSize(), { 0.5, 0.6 }))
	// {
	// 	Sprite button(count == chosenButton.y ? pauseTextures.at(2) : pauseTextures.at(3));
	// 	button.setPosition(i);
	// 	sprites.push_back(button);

	// 	if (count < sizeof(text) / sizeof(Text)) //precaution
	// 	{
	// 		text.at(count).setFillColor(Color::Black);
	// 		text.at(count).setOutlineColor(count == chosenButton.y ? Color(77, 193, 193) : Color(82, 119, 119));
	// 		text.at(count).setOutlineThickness(2);
	// 		text.at(count).setCharacterSize(button.getGlobalBounds().height / 2);

	// 		float textOffsetX = (button.getGlobalBounds().width - text.at(count).getGlobalBounds().width) / 2;
	// 		float textOffsetY = (button.getGlobalBounds().height - text.at(count).getCharacterSize()) / 2;
	// 		Vector2f textPosition = i + Vector2f{ textOffsetX, textOffsetY };
	// 		text.at(count).setPosition(textPosition);
	// 		texts.push_back(text.at(count));
	// 	}

	// 	count++;
	// }

	for (auto& i : sprites)
		nativeResolutionBuffer.draw(i);

	for (auto& i : texts)
		nativeResolutionBuffer.draw(i);

	nativeResolutionBuffer.display();
	Sprite finalOutput(nativeResolutionBuffer.getTexture()); // get final result from the buffer

	//SCALE DOWN FOR RESOLUTIONS LOWER THAN 1920/1080
	if (SHRINK_FACTOR != Vector2f{ 1, 1 })
		finalOutput.setScale(SHRINK_FACTOR);

	window.draw(finalOutput);
	window.display();
}

//FULLY DONE (HARDCODED)
int showScreenPause(RenderWindow& window, const vector<Texture>& pauseTextures, const Font& pauseFont)
{
	const Vector2u pauseGrid = { 1, 4 };
	Vector2u chosenButton = {1, 1};
	bool redraw = true;
	Event event;

	RenderTexture pauseTexture;
	pauseTexture.create(window.getSize().x, window.getSize().y);

	while (true)
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Escape)
				{
					return 1;
				}
				else if (event.key.code == Keyboard::E)
				{
					if (chosenButton.y == 1)
						return 1;
					else if (chosenButton.y == 2)
						return 2;
					else if (chosenButton.y == pauseGrid.y)
						return 0;
				}
				//if this returns false, Event::KR event does not satisfy any contitions so it is dismissed and redraw is not needed
				// else if (!gridEvent(event, pauseGrid, chosenButton)) 
				// 	continue;

				redraw = true;
			}

			//this event is unlikely, so it's placed below Event::KR
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

		// is there a need to redraw the menu
		if (redraw)
		{
			drawPause(window, pauseTextures, pauseFont, pauseGrid, chosenButton);
			redraw = false;
		}
	}
}



// void drawInventory(RenderWindow& window, const RenderTexture& background, const vector<Texture>& inventoryTextures, const Font& inventoryFont,
// 	const Vector2u& inventoryGrid, const int chosenItem, const Player& player)
// {
// 	window.clear();

// 	RenderTexture nativeResolutionBuffer;
// 	nativeResolutionBuffer.create(NATIVE_RESOLUTION.x, NATIVE_RESOLUTION.y);

// 	vector<Sprite> sprites;
// 	vector<Text> text;

// 	Sprite inventoryFrame{ inventoryTextures.at(0) };
// 	const Vector2f inventoryFramePosition = getCenterAlignment(inventoryFrame, Vector2f{ NATIVE_RESOLUTION });
// 	inventoryFrame.setPosition(inventoryFramePosition);
// 	sprites.push_back(inventoryFrame);

// 	unsigned int count = 0;
// 	for (auto& i : constructGrid(inventoryGrid, inventoryTextures.at(2).getSize(), nativeResolutionBuffer.getSize(), { 0.5,0.5 }))
// 	{
// 		Sprite itemFrame(chosenItem == count ? inventoryTextures.at(2) : inventoryTextures.at(3));
// 		itemFrame.setPosition(i);
// 		sprites.push_back(itemFrame);
// 		if (player.inventorySlots.at(count))
// 		{
// 			Sprite item(*itemList.at(player.inventorySlots.at(count) - 1).sprite.getTexture()); //wtf
// 			item.setPosition(itemFrame.getPosition() + getCenterAlignment(item, itemFrame));
// 			sprites.push_back(item);
// 		}
// 		count++;
// 	}
	
// 	for (auto& i : sprites)
// 		nativeResolutionBuffer.draw(i);

// 	//
// 	//
// 	//-----------------DRAW HERE
// 	//
// 	//
	
// 	nativeResolutionBuffer.display();
// 	Sprite finalOutput(nativeResolutionBuffer.getTexture());

// 	//SCALE DOWN FOR RESOLUTIONS LOWER THAN 1920/1080
// 	if (SHRINK_FACTOR != Vector2f{ 1, 1 })
// 		finalOutput.setScale(SHRINK_FACTOR);

// 	//draw background first
// 	window.draw(Sprite{ background.getTexture() });

// 	//tint it
// 	RectangleShape tint;
// 	tint.setSize(Vector2f{ window.getSize() });
// 	tint.setFillColor(Color{ 0, 0, 0, 170 });
// 	window.draw(tint);

// 	//draw the rest
// 	window.draw(finalOutput);
// 	window.display();
// }


// int showScreenInventory(RenderWindow& window, const RenderTexture& background, const vector<Texture>& inventoryTextures, const Font& inventoryFont, 
// 	Player& player, vector<gameObject>& objects)
// {
// 	srand(time(0));
// 	const Vector2u inventoryGrid = { 4,2 };

// 	bool redraw = true;
// 	int chosenItem = 0;
// 	Event event;

// 	while (true)
// 	{
// 		while (window.pollEvent(event))
// 		{
// 			if (event.type == Event::KeyReleased)
// 			{
// 				if (event.key.code == Keyboard::Escape or event.key.code == Keyboard::I)
// 				{
// 					return 0;
// 				}
// 				else if (event.key.code == Keyboard::Q)
// 				{
// 					if (player.inventorySlots.at(chosenItem))
// 					{
// 						gameObject droppedItem(itemList.at(player.inventorySlots.at(chosenItem) - 1));

// 						//should be changed to sprites (see finalDraw())
						
// 						droppedItem.body.setTexture(droppedItem.sprite.getTexture());
// 						droppedItem.body.setPosition(player.getCenter() + Vector2f( rand() % 20, rand() % 20 ));

// 						//items that player's able to pick up
// 						droppedItem.interactionType = 1;
// 						droppedItem.ID = 1;
// 						objects.push_back(droppedItem);
// 						player.inventorySlots.at(chosenItem) = 0;
// 					}
// 				}
// 				//if this returns false, Event::KR event does not satisfy any contitions so it is dismissed and redraw is not needed
// 				else if (!menuNavigation(event, inventoryGrid, chosenItem)) continue;

// 				redraw = true;
// 			}

// 			//this event is unlikely, so it's placed below Event::KR
// 			else if (event.type == Event::Closed)
// 			{
// 				window.close();
// 				return -1;
// 			}
// 		}

// 		if (redraw)
// 		{
// 			drawInventory(window, background, inventoryTextures, inventoryFont, inventoryGrid, chosenItem, player);
// 			redraw = false;
// 		}
// 	}
// }


// void applyPlayerInput(Player& player, vector<Projectile>& projectiles, const Clock& mainClock)
// {
// 	player.upPressed = (Keyboard::isKeyPressed(Keyboard::W) ? true : false);
// 	player.rightPressed = (Keyboard::isKeyPressed(Keyboard::D) ? true : false);
// 	player.downPressed = (Keyboard::isKeyPressed(Keyboard::S) ? true : false);
// 	player.leftPressed = (Keyboard::isKeyPressed(Keyboard::A) ? true : false);
// 	player.leftShiftPressed = (Keyboard::isKeyPressed(Keyboard::LShift) ? true : false);

// 	if (Keyboard::isKeyPressed(Keyboard::Space))
// 	{
// 		player.weapon.action(projectiles, player, mainClock);
// 		//if (player.weapon.isMelee and !(getTimeDiff(mainClock, player.weapon.latestShotTime) > player.weapon.projectileLifetime))
// 		//	player.isUsingWeapon = true; //false?
// 	}
// }


// void projectileHandlerMain(const Clock& mainClock, vector<Projectile>& projectiles, vector<gameObject>& objects, Player& player, float& testTime)
// {
// 	Clock testClock;
// 	// remove melee HB with expired swing or ranged projectiles with exceeding distance
// 	// before anything else
// 	projectiles.erase(remove_if(projectiles.begin(), projectiles.end(), [mainClock](const Projectile& projectile)
// 		{ return projectile.isMelee and getTimeDiff(mainClock, projectile.creationTime) > projectile.lifeTime ? true :
// 		!projectile.isMelee and projectile.traveledDistance > projectile.range ? true : false; }), projectiles.end());

// 	for (size_t i = 0; i < projectiles.size(); i++)
// 	{
// 		//MELEE
// 		if (projectiles.at(i).isMelee)
// 		{
// 			projectiles.at(i).body.setPosition(player.body.getPosition() + projectiles.at(i).swingHandle(mainClock));

// 			//check collisions
// 			for (size_t j = 1; j < objects.size(); j++)
// 			{
// 				if (projectiles.at(i).collisionCheck(objects.at(j)) and objects.at(j).isDestroyable and projectiles.at(i).penetration)
// 				{
// 					projectiles.at(i).penetration--;
// 					objects.erase(objects.begin() + j);
// 					j--;
// 				}
// 			}
// 		}
// 		//RANGED
// 		else
// 		{
// 			projectiles.at(i).updatePosition(mainClock.getElapsedTime().asSeconds());
// 			projectiles.at(i).traveledDistance += projectiles.at(i).latestDistanceCovered;

// 			//check collisions
// 			for (size_t j = 1; j < objects.size(); j++)
// 			{
// 				if (projectiles.at(i).collisionCheck(objects.at(j)))
// 				{
// 					if (objects.at(j).isDestroyable)
// 					{
// 						objects.erase(objects.begin() + j);
// 						j--;

// 						if (projectiles.at(i).penetration)
// 						{
// 							projectiles.at(i).penetration--;
// 							continue; //continue checking collisions for the same projectile
// 						}
// 					}

// 					projectiles.erase(projectiles.begin() + i);
// 					i--;
// 					break;
// 				}
// 			}
// 		}
// 	}
// 	player.weapon.reloadHandle(mainClock);
// 	testTime += testClock.getElapsedTime().asSeconds();
// }


// void objectHandlerMain(RenderWindow& window, vector<gameObjectStationary>& walls, vector<gameObject>& objects, Player& player)
// {
// 	bool interactionMessageDisplayed = false;
// 	bool needOverride = false;
	
// 	for (size_t i = 0; i < walls.size(); i++)
// 	{
// 		if (player.collisionCheck(walls.at(i), needOverride))
// 		{
// 			if (!walls.at(i).interactionType)
// 				continue;
// 			//otherwise collision and interaction ability are both present, handle them
// 		}
// 		else if (walls.at(i).interactionType)
// 		{
// 			if (!player.interactionCheck(walls.at(i)))
// 				continue;
// 			//otherwise interaction ability and interaction zone collision are both present, handle them
// 		}


// 		//if both conditions are not satisfied 
// 		//handle interactable gOS options
// 		if (player.interactionFlag)
// 		{
// 			//
// 			//interaction with gOS should be HERE
// 			//
// 			player.interactionFlag = false;
// 		}
// 		else if (!interactionMessageDisplayed)
// 		{
// 			//
// 			//interaction message display should be HERE
// 			//
// 			interactionMessageDisplayed = true;
// 		}
// 	}

// 	//gameObject handler
// 	for (size_t i = 0; i < objects.size(); i++)
// 	{
// 		if (player.collisionCheck(objects.at(i), needOverride))
// 		{
// 			if (!objects.at(i).interactionType)
// 				continue;
// 			//otherwise collision and interaction ability are both present, handle them
// 		}
// 		else if (objects.at(i).interactionType)
// 		{
// 			if (!player.interactionCheck(objects.at(i)))
// 				continue;
// 			//otherwise interaction ability and interaction zone collision are both present, handle them
// 		}


// 		//if both conditions are not satisfied 
// 		//handle interactable gO options
// 		if (player.interactionFlag)
// 		{
// 			//
// 			//interaction with gO should be HERE
// 			//
// 			// EXAMPLE: 
// 			if (objects.at(i).interactionType == 1)
// 			{
// 				for (auto& j : player.inventorySlots)
// 				{
// 					if (!j)
// 					{
// 						j = objects.at(i).ID;
// 						player.interactionFlag = false;
// 						objects.erase(objects.begin() + i);
// 						i--;
// 						break;
// 					}
// 				}
// 			}
// 			//
// 			//
// 			//
// 		}
// 		else if (!interactionMessageDisplayed)
// 		{
// 			//
// 			//interaction message display should be HERE
// 			//
// 			// EXAMPLE: 
// 			RectangleShape msg;
// 			msg.setSize(Vector2f(20, 5));
// 			msg.setPosition(Vector2f(player.body.getPosition() + Vector2f(0, -10)));
// 			msg.setFillColor(Color(Color::White));
// 			window.draw(msg);
// 			//
// 			//
// 			interactionMessageDisplayed = true;
// 		}
// 	}
// 	if (!needOverride)
// 		player.overrideInputX = player.overrideInputY = false;
// }

#pragma warning(pop)