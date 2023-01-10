#pragma once

#include <vector>
using std::vector;

#include <SFML/Graphics.hpp>
using sf::Texture, sf::RenderWindow;


extern const std::string DIRECTORY;


void setWindowIcon(RenderWindow& window);


void loadTexturesMenu(vector<Texture>& menuTextures);


void loadTexturesPause(vector<Texture>& pauseTextures);


void loadTexturesInventory(vector<Texture>& inventoryTextures);


void loadTextures(vector<Texture>& textures);
