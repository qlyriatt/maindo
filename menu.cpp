#include "menu.h"

#include "resources.h"
#include "Misc.h"

Menu::Menu(GameObject *parent) : 
    GameObject(parent),
    is_first_draw_(true),
    lightup_interval_(3),
    stored_time_{},
    latest_animation_update_{},
    grid_(1, 4),
    current_cell_(0, 0)
{
}

void Menu::setQuitFunc(std::function<void()> quit_func)
{
    quit_func_ = quit_func;
}

bool Menu::processEvent(const Event &event)
{
    if (event.type == Event::KeyReleased)
    {
        if (event.key.code == Keyboard::E)
        {
            if (current_cell_.y == 1)
            {
                load();
                return true;
            }
            else if (current_cell_.y == 2)
            {
                load();
                return true;
            }
            else if (current_cell_.y == grid_.y)
            {
                quit();
                return true;
            }
        }
        else return menuNavigation(event, grid_, current_cell_);
    }

    return false;
}

void Menu::quit()
{
    quit_func_();
}

void Menu::draw(RenderWindow &window)
{
    RenderTexture native_res_buf;
    native_res_buf.create(NATIVE_RESOLUTION.x, NATIVE_RESOLUTION.y);

    vector<Sprite> sprites;
    vector<Text> texts;

    // main menu background
    Sprite background(resources().menu_textures_.at(1));
    sprites.push_back(background);

    // main menu buttons text
    const auto font = resources().font_;
    vector<Text> text{{}, {"Continue", font}, {"New Game", font}, {"Whatever", font}, {"Quit", font}};
    int count = 1;

    // create buttons
    for (auto &i : constructGrid(grid_, resources().menu_textures_.at(2).getSize(), native_res_buf.getSize(), {0.5, 0.6} /*C4305*/))
    {
        Sprite button(count == current_cell_.y ? resources().menu_textures_.at(2) : resources().menu_textures_.at(3));
        button.setPosition(i);
        sprites.push_back(button);

        text.at(count).setFillColor(Color::Black);
        text.at(count).setOutlineColor(count == current_cell_.y ? Color(175, 58, 210) : Color(112, 37, 135));
        text.at(count).setOutlineThickness(2);
        text.at(count).setCharacterSize(button.getGlobalBounds().height / 2);

        float textOffsetX = (button.getGlobalBounds().width - text.at(count).getGlobalBounds().width) / 2;
        float textOffsetY = (button.getGlobalBounds().height - text.at(count).getCharacterSize()) / 2;
        Vector2f text_pos = i + Vector2f{textOffsetX, textOffsetY};
        text.at(count).setPosition(text_pos);
        texts.push_back(text.at(count));

        count++;
    }

    for (auto &i : sprites)
        native_res_buf.draw(i);

    for (auto &i : texts)
        native_res_buf.draw(i);

    // on first load the menu is tinted
    if (is_first_draw_)
    {
        RectangleShape tint;
        tint.setSize(Vector2f{native_res_buf.getSize()});
        if (stored_time_ < lightup_interval_)
        {
            // opacity goes from 0 to 255, making the tint go from black to transparent
            tint.setFillColor(Color(0, 0, 0, 255 * (1 - stored_time_ / lightup_interval_)));
            native_res_buf.draw(tint);
            stored_time_ += clock_.getElapsedTime().asSeconds() - latest_animation_update_;
            latest_animation_update_ = clock_.getElapsedTime().asSeconds();
        }
        else
        {
            is_first_draw_ = false;
            stored_time_ = latest_animation_update_ = 0;
        }
    }

    native_res_buf.display();
    Sprite finalOutput(native_res_buf.getTexture()); // get final result from the buffer

    // SCALE DOWN FOR RESOLUTIONS LOWER THAN 1920/1080
    if (SHRINK_FACTOR != Vector2f{1, 1})
        finalOutput.setScale(SHRINK_FACTOR);

    window.draw(finalOutput);
}
