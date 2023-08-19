#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;

using std::vector;

class GameObject
{
public:
    GameObject(GameObject *parent);

    bool event(const Event &event);
    virtual void draw(RenderWindow &window) = 0;
protected:
    virtual bool processEvent(const Event &event) = 0;
private:
    GameObject *parent_;
    vector<GameObject *> children_;
};