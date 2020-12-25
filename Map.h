#pragma once
#include "Player.h"
#include "Entity.h"

#include <iostream>
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;


extern const std::string DIRECTORY;


//lots of work waiting
void initialize(int map_type, vector<gameObject>& objects, vector<Entity>& entities, const vector<Texture>& textures);


void saveLevel(int currentLevel, const vector<gameObject>& objects, const vector<Entity>& entities, const vector<Texture>& textures);


void loadLevel(const int number, vector<gameObject>& objects);
