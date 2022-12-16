#include "BasicObject.h";


inline bool BasicObject::collisionCheck(const FloatRect& obstacle) const
{
	if (body.getGlobalBounds().intersects(obstacle))
		return true;
	return false;
}

bool BasicObject::collisionCheck(const RectangleShape& obstacle) const
{
	if (collisionCheck(obstacle.getGlobalBounds()))
		return true;
	return false;
}

bool BasicObject::collisionCheck(const BasicObject& obstacle) const
{	
	if (collisionCheck(obstacle.body.getGlobalBounds()))
		return true;
	return false;
}
