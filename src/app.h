#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <vector>

class GameObject;

class App : public sf::RenderWindow
{
public:
    explicit App(int argc, char *argv[]);
    bool execute();

    static std::string appdir();
    static std::string resdir();
private:
    void init();

    void pollEvents();
    void event(const sf::Event &event);

    void draw();
    void showMenu();
private:
    sf::Clock main_clock_;

    sf::View camera_;
    sf::View minimap_;
    sf::RenderTexture main_texture_;
    sf::RenderTexture minimap_texture_;

    std::vector<GameObject *> children_;
};

