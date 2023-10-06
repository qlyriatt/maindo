#pragma once
#include <time.h>
#include <vector>
using std::vector;


#include "Player.h"
#include "Utilities.h"

extern const std::string DIRECTORY;
const Vector2f WINDOW_SIZE{ 1920, 1080 };
const Vector2f CAMERA_SIZE{ 1920, 1080 };
const Vector2f INVENTORY_SIZE{ CAMERA_SIZE / 2.f };
const Vector2u NATIVE_RESOLUTION = { 1920, 1080 };
const Vector2f SHRINK_FACTOR = { WINDOW_SIZE.x / 1920, WINDOW_SIZE.y / 1080 };

#define DEBUG_LEVEL 1







//every possible use(less)(ful) function that can be thought of


/////////////////////////////////////////////////
/// @brief Gets current animation state based on time diffetence
/// @param storedTimeDifference Time elapsed since the beginning of animation cycle
/// @param animationStates How much animation states are provided
/// @param changesPerSecondMultiplier Animation speed multiplier
/// @return Current animation state
/////////////////////////////////////////////////
int getCount(float storedTimeDifference, int animationStates, const size_t changesPerSecondMultiplier = 1);


/////////////////////////////////////////////////
/// @brief Aligns time differences after switching to menus (pause, inventory etc.)
/// @param timestamp Time on menu entering
/// @param clock Main clock
/// @param player Player instance
/// @param objects Vector containing objects
/// @param projectiles Vector containing projectiles
/////////////////////////////////////////////////
//void alignTime(const float timestamp, const Clock& clock, Player& player, vector<gameObject>& objects, vector<Projectile>& projectiles);


/////////////////////////////////////////////////
/// @brief Draws everything in the current frame
///
/// @param renderTexture RenderTexture to draw to
/////////////////////////////////////////////////
// void finalDraw(RenderTexture& renderTexture, const vector<gameObject>& objects, const vector<Entity>& entities, const vector<Projectile>& projectiles,
// 	const Player& player);


// void finalDrawMinimap(RenderTexture& renderTexture, vector<gameObject>& objects, vector<Entity>& entities,
// 	vector<Projectile>& projectiles, Player& player);


// void levelLoad(RenderWindow& window, vector<gameObject>& objects, vector<Entity>& entities, int& currentLevel, int switchToLevel, const vector<Texture>& textures);


// void cameraCollision(const gameObject& area, View& camera, const Player& player, const Vector2f WINDOW_SIZE);


/////////////////////////////////////////////////
/// @brief Simple function to navigate any menu 
/// NOTE : count should be a non-const reference
/// 
/// @param event Event to handle
/// 
/// @return True if event was handled succesfully, false otherwise
/////////////////////////////////////////////////
bool gridEvent(const Event& event, int rows, int columns, int &current_row, int &current_column);


vector<Vector2f> gridLayout(int rows, int columns, const Vector2u& cell_size, const Vector2u& target_size,
	const Vector2f& alignment_factor = {0.5, 0.5}, const Vector2f& cell_gap_factor = {0, 0});

/////////////////////////////////////////////////
/// @brief Pause menu drawer function
/////////////////////////////////////////////////
void drawPause(RenderWindow& window, const vector<Texture>& pauseTextures, const Font& pauseFont, const Vector2u& pauseGrid,
	const Vector2u& chosenButton);


/////////////////////////////////////////////////
/// @brief Draws pause menu and allows interaction
///
/// @param window Main render window
/// @param pauseTextures Textures to use 
/// @param pauseFont Font to use
/// 
/// @return
/////////////////////////////////////////////////
int showScreenPause(RenderWindow& window, const vector<Texture>& pauseTextures, const Font& pauseFont);




/////////////////////////////////////////////////
/// @brief Inventory drawer function
/////////////////////////////////////////////////
// void drawInventory(RenderWindow& window, const RenderTexture& background,
// 	const vector<Texture>& inventoryTextures, const Font& inventoryFont, const Vector2u& inventoryGrid, const Vector2u& chosenItem, const Player& player);


/////////////////////////////////////////////////
/// @brief Draws pause menu and allows interaction
///
/// @param window Main render window
/// @param background What was on the screen on inventory call (usually mainGameTexture) 
/// @param inventoryTextures Textures to use
/// @param inventoryFont Font to use
/// @param player Player instance
/// @param objects Vector containing objects to handle item drops
/// 
/// @return
/////////////////////////////////////////////////
// int showScreenInventory(RenderWindow& window, const RenderTexture& background, const vector<Texture>& inventoryTextures, const Font& inventoryFont, 
// 	Player& player, vector<gameObject>& objects);


/////////////////////////////////////////////////
/// @brief Applies keyboard input to the current player state:
///
/// W : move up
/// A : move left
/// S : move down
/// D : move right
/// E : interact
/// I : open inventory
/// Esc : open pause menu
/// Spacebar : use current weapon
/// R : switch weapons
/// 
/// @param player Player instance
/// @param projectiles Reference to the vector containing projectiles
/// @param mainClock Main game clock
/////////////////////////////////////////////////
//void applyPlayerInput(Player& player, vector<Projectile>& projectiles, const Clock& mainClock);


/////////////////////////////////////////////////
/// @brief Handles interaction with projectile vector, such as :
///
///	Collision checking
/// Projectile erasing based on lifetime, distance or collisions
/// Objects erasing based on collisions
/// 
/// @param mainClock Main game clock
/// @param projectiles Reference to the vector containing projectiles
/// @param objects Reference to the vector containing objects
/// @param Player instance to handle reloads
/////////////////////////////////////////////////
//void projectileHandlerMain(const Clock& mainClock, vector<Projectile>& projectiles, vector<gameObject>& objects, Player& player, float& testTime);


/////////////////////////////////////////////////
/// @brief Handles collisions and interactions with both stationary and moving objects
///
/// @param walls Vector containing stationary objects
/// @param objects Vector containing moving objects
/// @param player Player instance
/// @param needOverride Does input need to be overriden
/// @param interactionMessageDisplayed Is intera
//void objectHandlerMain(RenderWindow& window, vector<gameObjectStationary>& walls, vector<gameObject>& objects, Player& player);
