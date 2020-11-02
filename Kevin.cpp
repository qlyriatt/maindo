#include  <SFML/Graphics.hpp>
#include <iostream>
#include "windows.h"
#include "Actor.h"
#include "Kevin.h"

using namespace std;
using namespace sf;

Kevin::Kevin(Vector2f& size, Vector2f& position, Color& color) : Actor(size, position, color) {}