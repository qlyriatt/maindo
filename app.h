#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using std::vector;

class GameObject;

class App : public RenderWindow
{
public:
    bool execute();

private:
    void init();

    void pollEvents();
    void event(const Event &event);

    void draw();
    void showMenu();
private:
    Clock main_clock_;

    View camera_;
    View minimap_;
    RenderTexture main_texture_;
    RenderTexture minimap_texture_;

    vector<GameObject *> children_;
};

