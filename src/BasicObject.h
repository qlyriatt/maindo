#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Sprite.hpp"

class BasicObject : public sf::Drawable
{
public:
    virtual ~BasicObject() = default;

    sf::RectangleShape body;

    inline bool collisionCheck(const sf::FloatRect &obstacle) const;

    bool collisionCheck(const sf::RectangleShape &obstacle) const;

    bool collisionCheck(const BasicObject &obstacle) const;

    virtual void updateState(){};

    void updateAnimation(float elapsedTime);

protected:
    bool allowCollision = false;
    bool isDestroyable = false;
    bool isAnimated = false;
    int animationStates = 0;
    float animationCycleTimer = 0;
    float latestAnimationUpdateTime = 0;
    sf::Sprite sprite;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};