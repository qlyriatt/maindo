#include <SFML/Graphics.hpp>

#include "Misc.h"
#include "Render.h"
#include "Player.h"

#include "app.h"


// INPUT --> PROJECTILE --> POSITION --> COLLISION CHECK --> CAMERA --> DRAW
//	 ^													|
//   |------------------INPUT OVERRIDE-------------------
//
//							current


// SPECIFY FOLDER WITH GAME FILES
const std::string APPDIR;
const std::string RESDIR;

//vector<gameObject> itemList;
#include <iostream>
int main(int argc, char *argv[])
{
	App app(argc, argv);
	return app.execute();
}


