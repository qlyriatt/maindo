#include "resources.h"

#include "Render.h"

Resources::Resources()
{
    // fonts
    font_.loadFromFile(DIRECTORY + "gnomoria.ttf");

    // textures
    loadTexturesMenu(menu_textures_);
    loadTexturesPause(pause_textures_);
    loadTexturesInventory(inventory_textures_);
    loadTextures(textures_);
}

const Resources &resources()
{
    static Resources instance;
    return instance;
}
