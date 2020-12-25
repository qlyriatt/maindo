#pragma once
#include "Map.h"

#include <time.h>



extern const std::string DIRECTORY;
//const Vector2f WINDOW_SIZE{ 1920, 1080 };
const Vector2f WINDOW_SIZE{ 1366, 768 };
//const Vector2f CAMERA_SIZE{ 1920, 1080 };
const Vector2f CAMERA_SIZE{ 1366, 768 };
const Vector2f INVENTORY_SIZE{ CAMERA_SIZE / 2.f };
const Vector2u NATIVE_RESOLUTION = { 1920, 1080 };
const Vector2f SHRINK_FACTOR = { WINDOW_SIZE.x / 1920, WINDOW_SIZE.y / 1080 };

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

String pickName();


float getTimeDiff(const Clock& clock, float time);


int getCount(float storedTimeDifference, int animationStates, int changesPerSecondMultiplier = 1);


//aligns latestTimeUpdate (or else) for everything after additional rendering
void alignTime(const float timestamp, const Clock& clock, Player& player, vector<gameObject>& objects, vector<Projectile>& projectiles);


/////////////////////////////////////////////////
/// @brief Changes opacity of an object
///
/// @param object Target
/// @param opacity Opacity to set, default is non-transparent
/////////////////////////////////////////////////
void setOpacity(gameObjectStationary& object, int opacity = 255);


void loadTexturesMenu(vector<Texture>& menuTextures);


void loadTexturesPause(vector<Texture>& pauseTextures);


void loadTextures(vector<Texture>& textures);


/////////////////////////////////////////////////
/// @brief Draws everything in the current frame
///
/// @param renderTexture RenderTexture to draw to
/////////////////////////////////////////////////
void finalDraw(RenderTexture& renderTexture, const vector<gameObject>& objects, const vector<Entity>& entities, const vector<Projectile>& projectiles,
	const Player& player);


void finalDrawMinimap(RenderTexture& renderTexture, vector<gameObject>& objects, vector<Entity>& entities,
	vector<Projectile>& projectiles, Player& player);


void levelLoad(RenderWindow& window, vector<gameObject>& objects, vector<Entity>& entities, int& currentLevel, int switchToLevel, const vector<Texture>& textures);


void cameraCollision(const gameObject& area, View& camera, const Player& player, const Vector2f WINDOW_SIZE);


/////////////////////////////////////////////////
/// @brief Simple function to navigate any menu 
/// NOTE : count should be a non-const reference
/// 
/// @param event Event to handle
/// @param gridDimensions Menu grid dimensions (X = rows, Y = columns)
/// @param count Reference to current menu count (button, item, etc.)
/// 
/// @return True if event was handled succesfully, false otherwise
/////////////////////////////////////////////////
bool menuNavigation(const Event& event, const Vector2u& gridDimensions, int& count);


/////////////////////////////////////////////////
// Very (not)useful calculations that help solve the great (unexisting) problem of
// having to construct many grid-like sets of objects by making it ten millions times harder 
// than it actually is, and all thanks to standartisation and code reusage, 
// because making one function do anything for everything was a BRILLIANT IDEA!!!
/////////////////////////////////////////////////
vector<Vector2f> constructGrid(const Vector2u& gridDimensions, const Vector2u& textureSize, const Vector2u& renderTargetSize,
	const Vector2f& alignmentFactor, const Vector2f& cellOffsetFactor = { 0, 0 });


/////////////////////////////////////////////////
/// @brief Main menu drawer function
/////////////////////////////////////////////////
void drawMenu(RenderWindow& window, const vector<Texture>& menuTextures, const Font& menuFont, const Vector2u& menuGrid,
	const int chosenButton, const Clock& clock, float& storedTime, float& latestAnimationUpdate, bool& isFirstDraw);


/////////////////////////////////////////////////
/// @brief Draws main menu and allows menu interaction
///
/// @param window Main render window
/// @param menuTextures Textures used in menu drawing
/// @param menuFont Font used in menu drawing
/// 
/// @returns -1 if the window was closed, 0 if level is loading from save, otherwise a level to load
/////////////////////////////////////////////////
int showScreenMenu(RenderWindow& window, const vector<Texture>& menuTextures, const Font& menuFont);


/////////////////////////////////////////////////
/// @brief Pause menu drawer function
/////////////////////////////////////////////////
void drawPause(RenderWindow& window, const vector<Texture>& pauseTextures, const Font& pauseFont, const Vector2u& pauseGrid,
	const int chosenButton);


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
void drawInventory(RenderWindow& window, const RenderTexture& background,
	const vector<Texture>& inventoryTextures, const Font& inventoryFont, const Vector2u& inventoryGrid, const int chosenItem);


/////////////////////////////////////////////////
/// @brief Draws pause menu and allows interaction
///
/// @param window Main render window
/// @param background What was on the screen on inventory call (usually mainGameTexture) 
/// @param textures Textures to use
/// @param font Font to use
/// 
/// @return
/////////////////////////////////////////////////
int showScreenInventory(RenderWindow& window, const RenderTexture& background, const vector<Texture>& inventoryTextures, const Font& inventoryFont, Player& player);


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
void applyPlayerInput(Player& player, vector<Projectile>& projectiles, const Clock& mainClock);


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
void projectileHandlerMain(const Clock& mainClock, vector<Projectile>& projectiles, vector<gameObject>& objects, Player& player, float& testTime);


/////////////////////////////////////////////////
/// @brief Handles collisions and interactions with both stationary and moving objects
///
/// @param walls Vector containing stationary objects
/// @param objects Vector containing moving objects
/// @param player Player instance
/// @param needOverride Does input need to be overriden
/// @param interactionMessageDisplayed Is intera
void objectHandlerMain(RenderWindow& window, vector<gameObjectStationary>& walls, vector<gameObject> objects, Player& player);

