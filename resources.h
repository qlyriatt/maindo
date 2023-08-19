#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

using namespace sf;
using std::vector;

class Resources
{
    friend const Resources &resources();
public:
    vector<Texture> menu_textures_;
	vector<Texture> pause_textures_;
	vector<Texture> inventory_textures_;
	vector<Texture> textures_; 

    Font font_;
private:
    Resources();
};

const Resources &resources();
