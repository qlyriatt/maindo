#pragma once
#include <SFML/Graphics.hpp>
using sf::FloatRect, sf::RectangleShape, sf::Sprite;


class BasicObject : public sf::Drawable
{
protected:

    bool    allowCollision = false;
    bool    isDestroyable = false;
    bool    isAnimated = false;
    int     animationStates = 0;
    float   animationCycleTimer = 0;
    float   latestAnimationUpdateTime = 0;    
    Sprite  sprite;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    virtual ~BasicObject() = default;

    RectangleShape body;
        
    inline bool collisionCheck(const FloatRect& obstacle) const;

    bool collisionCheck(const RectangleShape& obstacle) const;

    bool collisionCheck(const BasicObject& obstacle) const; 

    virtual void updateState() {};

    void updateAnimation(float elapsedTime);
    
};