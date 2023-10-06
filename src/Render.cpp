#include "Render.h"
#include "app.h"

void loadTexturesMenu(vector<Texture>& menuTextures)
{
	Texture menuLight;
	menuLight.loadFromFile(App::resdir() + "textures/menuLight.png");
	menuTextures.push_back(menuLight);

	Texture menuDark;
	menuDark.loadFromFile(App::resdir() + "textures/menuDark.png");
	menuTextures.push_back(menuDark);

	Texture menuButtonLight;
	menuButtonLight.loadFromFile(App::resdir() + "textures/menuButtonLight.png");
	menuTextures.push_back(menuButtonLight);

	Texture menuButtonDark;
	menuButtonDark.loadFromFile(App::resdir() + "textures/menuButtonDark.png");
	menuTextures.push_back(menuButtonDark);
}


void loadTexturesPause(vector<Texture>& pauseTextures)
{
	Texture menuLight;
	menuLight.loadFromFile(App::resdir() + "textures/pauseLight.png");
	pauseTextures.push_back(menuLight);

	Texture menuDark;
	menuDark.loadFromFile(App::resdir() + "textures/pauseDark.png");
	pauseTextures.push_back(menuDark);

	Texture menuButtonLight;
	menuButtonLight.loadFromFile(App::resdir() + "textures/pauseButtonLight.png");
	pauseTextures.push_back(menuButtonLight);

	Texture menuButtonDark;
	menuButtonDark.loadFromFile(App::resdir() + "textures/pauseButtonDark.png");
	pauseTextures.push_back(menuButtonDark);
}


void loadTexturesInventory(vector<Texture>& inventoryTextures)
{
	Texture inventoryLight;
	inventoryLight.loadFromFile(App::resdir() + "textures/inventoryLight.png");
	inventoryTextures.push_back(inventoryLight);

	//CHANGE LATER
	Texture inventoryDark;
	inventoryDark.loadFromFile(App::resdir() + "textures/inventoryLight.png");
	inventoryTextures.push_back(inventoryDark);

	Texture itemFrameLight;
	itemFrameLight.loadFromFile(App::resdir() + "textures/itemFrameLight.png");
	inventoryTextures.push_back(itemFrameLight);

	Texture itemFrameDark;
	itemFrameDark.loadFromFile(App::resdir() + "textures/itemFrameDark.png");
	inventoryTextures.push_back(itemFrameDark);

}


void loadTextures(vector<Texture>& textures)
{
	
	Texture backgroundTexture;
	backgroundTexture.loadFromFile(App::resdir() + "textures/background.jpg");
	textures.push_back(backgroundTexture);
	
	Texture playerTexture;
	playerTexture.loadFromFile(App::resdir() + "textures/player.png");
	textures.push_back(playerTexture);

	Texture bulletPistolTexture;
	bulletPistolTexture.loadFromFile(App::resdir() + "textures/bulletPistol.png");
	textures.push_back(bulletPistolTexture);

	Texture bulletRifleTexture;
	bulletRifleTexture.loadFromFile(App::resdir() + "textures/bulletRifle.png");
	textures.push_back(bulletRifleTexture);
}

