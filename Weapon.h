#pragma once
#include  <SFML/Graphics.hpp>
#include "gameObject.h"

using namespace std;
using namespace sf;


enum weaponId {
	keyboard = 0,
	mouse,
	stapler,
	staple
};

class Weapon : public gameObject {
private:

	uint8_t damage;
	uint16_t damageDistance;
	uint8_t weaponId;
};