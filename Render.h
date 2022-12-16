#include <SFML/Graphics.hpp>
using namespace sf;

#include <vector>
using std::vector;

extern const std::string DIRECTORY;


void setWindowIcon(RenderWindow& window);


void loadTexturesMenu(vector<Texture>& menuTextures);


void loadTexturesPause(vector<Texture>& pauseTextures);


void loadTexturesInventory(vector<Texture>& inventoryTextures);


void loadTextures(vector<Texture>& textures);
