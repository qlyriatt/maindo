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
const std::string DIRECTORY = { "/home/qlyriatt/code/maindo/" };

//vector<gameObject> itemList;

int main()
{
	App app;
	return app.execute();
}


