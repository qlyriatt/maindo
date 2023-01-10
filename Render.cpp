#include "Render.h"


void setWindowIcon(RenderWindow& window)
{
    sf::Image icon;
	icon.loadFromFile(DIRECTORY + "Textures/icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
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


void loadTexturesInventory(vector<Texture>& inventoryTextures)
{
	Texture inventoryLight;
	inventoryLight.loadFromFile(DIRECTORY + "Textures/inventoryLight.png");
	inventoryTextures.push_back(inventoryLight);

	//CHANGE LATER
	Texture inventoryDark;
	inventoryDark.loadFromFile(DIRECTORY + "Textures/inventoryLight.png");
	inventoryTextures.push_back(inventoryDark);

	Texture itemFrameLight;
	itemFrameLight.loadFromFile(DIRECTORY + "Textures/itemFrameLight.png");
	inventoryTextures.push_back(itemFrameLight);

	Texture itemFrameDark;
	itemFrameDark.loadFromFile(DIRECTORY + "Textures/itemFrameDark.png");
	inventoryTextures.push_back(itemFrameDark);

}


void loadTextures(vector<Texture>& textures)
{
	
	Texture backgroundTexture;
	backgroundTexture.loadFromFile(DIRECTORY + "Textures/background.jpg");
	textures.push_back(backgroundTexture);
	
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

