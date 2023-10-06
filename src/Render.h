#pragma once

#include <vector>
using std::vector;

#include <SFML/Graphics.hpp>
using sf::Texture, sf::RenderWindow;

void loadTexturesMenu(vector<Texture>& menuTextures);


void loadTexturesPause(vector<Texture>& pauseTextures);


void loadTexturesInventory(vector<Texture>& inventoryTextures);


void loadTextures(vector<Texture>& textures);
