#include <SFML/Graphics.hpp>

#include "BasicObject.h"
using namespace sf;


//pls help
namespace sf
{
	template<typename T, typename U>
	Vector2f operator *(const Vector2<T>& left, const Vector2<U>& right)
	{
		return Vector2f(left.x * right.x, left.y * right.y);
	}

	template<typename T>
	Vector2<T> operator *(const Vector2<T>& left, const Vector2<T>& right)
	{
		return Vector2<T>(left.x * right.x, left.y * right.y);
	}

	template<typename T, typename U>
	Vector2f operator /(const Vector2<T>& left, const Vector2<U>& right)
	{
		return Vector2f(float(left.x) / float(right.x), float(left.y) / float(right.y));
	}
};

namespace Utilities {
/////////////////////////////////////////////////
/// @brief Picks a name for the game window
/////////////////////////////////////////////////
String pickName();

/////////////////////////////////////////////////
/// @brief Get time difference between clock time and some stored time 
/// @param clock Clock
/// @param time Stored time variable
/// @return Time difference
/////////////////////////////////////////////////
float getTimeDiff(const Clock& clock, const float& time);


/////////////////////////////////////////////////
/// @brief Changes opacity of an object
///
/// @param object Target
/// @param opacity Opacity to set, default is non-transparent, lower is more transparent
/////////////////////////////////////////////////
void setOpacity(BasicObject& object, int opacity = 255);


/////////////////////////////////////////////////
/// @brief Produces a vector to align sprite in the middle of target
/// @param insideSprite What should be aligned
/// @param outsideAreaSize Where should it be aligned at
/// @return Vector to calculated position
/////////////////////////////////////////////////
Vector2f getCenterAlignment(const Sprite& insideSprite, const Vector2f& outsideAreaSize);


/////////////////////////////////////////////////
/// @brief Produces a vector to align sprite in the middle of target
/// @param inside What should be aligned
/// @param outside Where should it be aligned at
/// @return Vector to calculated position
/////////////////////////////////////////////////
Vector2f getCenterAlignment(const Sprite& insideSprite, const Sprite& outsideSprite);


Vector2f getCenter (RectangleShape rectangle);
}