#include <SFML/Graphics.hpp>
using namespace sf;


class BasicObject
{
protected:
    virtual ~BasicObject();

    bool allowCollision = {false};
    bool isDestroyable = {false};
    Sprite sprite;

public:
    BasicObject();

    RectangleShape body;
        
    inline bool collisionCheck(const FloatRect& obstacle) const;

    bool collisionCheck(const RectangleShape& obstacle) const;

    bool collisionCheck(const BasicObject& obstacle) const; 

    virtual void updateState();
};