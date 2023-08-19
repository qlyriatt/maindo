#pragma once

#include "gameobject.h"

#include <functional>

class Menu : public GameObject
{
public:
    Menu(GameObject *parent);

    void setQuitFunc(std::function<void()> quit_func);

    void draw(RenderWindow &window) override;
protected:
    bool processEvent(const Event &event) override;
private:
    void load() {};
    void quit();
private:
    bool is_first_draw_;
    const int lightup_interval_;
    double stored_time_;
    double latest_animation_update_;

    Clock clock_;
    Vector2u grid_;
    Vector2u current_cell_;

    std::function<void()> quit_func_;
};