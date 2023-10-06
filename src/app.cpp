#include "app.h"

#include "Misc.h"
#include "Render.h"
#include "Utilities.h"
#include "menu.h"
#include "resources.h"

std::string APPDIR;
std::string RESDIR;

App::App(int argc, char *argv[])
{
    APPDIR = argv[0];
    auto exec = std::find(APPDIR.crbegin(), APPDIR.crend(), '/');
    auto build = std::find(std::next(exec), APPDIR.crend(), '/');
    APPDIR.resize(APPDIR.size() - std::distance(APPDIR.crbegin(), build));
    RESDIR = APPDIR + "/res/";
}

bool App::execute()
{
    init();
    showMenu();

    while (isOpen())
    {
        pollEvents();

        clear();
        main_texture_.clear();
        minimap_texture_.clear();

        setView(camera_);
        draw();
        // player.interactionFlag = false;

        // if (inMenu)
        // {
        // 	// objects.erase(objects.begin(), objects.end());
        // 	// entities.erase(entities.begin(), entities.end());
        // 	// projectiles.erase(projectiles.begin(), projectiles.end());

        // 	switch (int chosenLevel = showScreenMenu(window, menuTextures, fontMain))
        // 	{
        // 	case -1:
        // 		cout << endl << testTime;
        // 		return -15;
        // 	case 0:
        // 		//loadLevel(objects, currentLevel);
        // 		break;
        // 	default:
        // 		levelLoad(window, objects, entities, currentLevel, chosenLevel, textures);
        // 		break;
        // 	}

        // 	for (int i = 0; i < 4; i++)
        // 	{
        // 		player.inventorySlots.at(i) = 1;
        // 	}
        // 	inMenu = false;
        // }

        // applyPlayerInput(player, projectiles, mainClock);
        // //---INPUT PHASE END

        // //---PROJECTILE PHASE
        // projectileHandlerMain(mainClock, projectiles, objects, player, testTime);
        // //---PROJECTILE PHASE END

        // //---POSITION PHASE
        // player.updatePosition(mainClock.getElapsedTime().asSeconds());
        // //---POSITION PHASE END

        // //---COLLISION PHASE

        // //oblivious
        // //
        // //should be split for gOS and gO (probably)
        // objectHandlerMain(window, walls, objects, player);

        // for (size_t i = 0; i < entities.size(); i++)
        // {
        // 	entities.at(i).script(Vector2f(400 + 100 * i, 300 + 100 * i), player.getCenter(), mainClock.getElapsedTime().asSeconds(), projectiles);
        // 	for (size_t j = 1; j < objects.size(); j++)
        // 	{
        // 		entities.at(i).collisionCheck(objects.at(j));
        // 	}
        // }

        //---COLLISION PHASE END

        //---DRAW PHASE

        // player.updateAnimation(mainClock.getElapsedTime().asSeconds(), &textures.at(0));

        // camera.setCenter(player.getCenter());
        // //cameraCollision(objects.at(0), camera, player, WINDOW_SIZE); //Vector2f(main_texture_.getSize()));
        // if (camera.getSize().x == CAMERA_SIZE.x / 8)
        // 	camera.setCenter(player.getCenter() - Vector2f(0, 10));
        // if (camera.getSize().x == CAMERA_SIZE.x / 16)
        // 	camera.setCenter(player.getCenter() - Vector2f(0, 20));

        // main_texture_.setView(camera);

        // minimap.setCenter(player.getCenter());
        // minimap_texture_.setView(minimap);

        // finalDraw(main_texture_, objects, entities, projectiles, player);

        // if (inInventory)
        // {
        // 	float timestamp = mainClock.getElapsedTime().asSeconds();
        // 	showScreenInventory(window, main_texture_, inventoryTextures, fontMain, player, objects);
        // 	alignTime(timestamp, mainClock, player, objects, projectiles);
        // 	inInventory = false;
        // }

        // window.draw(Sprite{ main_texture_.getTexture() });
        // //----------main draw cycle ends here----------
        // //
        // //at this point current game frame should be ready for display

        // RectangleShape hpBase;
        // hpBase.setPosition(30, 30);
        // hpBase.setSize(Vector2f(102, 22));
        // hpBase.setFillColor(Color::White);
        // window.draw(hpBase);
        // RectangleShape hpBar;
        // hpBar.setPosition(31, 31);
        // hpBar.setSize(Vector2f(player.health, 20));
        // hpBar.setFillColor(Color::Red);
        // window.draw(hpBar);

        // if (drawMinimap)
        // {
        // 	finalDrawMinimap(minimap_texture_, objects, entities, projectiles, player);

        // 	RectangleShape black;
        // 	black.setPosition(window.getSize()* Vector2f{ minimap.getViewport().left, minimap.getViewport().top });
        // 	black.setSize(window.getSize() * Vector2f{ minimap.getViewport().width, minimap.getViewport().height });
        // 	black.setFillColor(Color(0,0,0, 180));
        // 	black.setOutlineColor(Color::Red);
        // 	black.setOutlineThickness(2);

        // 	window.draw(black);
        // 	window.draw(Sprite{ minimap_texture_.getTexture() });
        // }

        // player.updatePosition(mainClock.getElapsedTime().asSeconds());
        // camera_.setCenter(Utilities::getCenter(player.body));
        // draw(bg);
        // draw(player);
        display();
        //---DRAW PHASE END
    }

    return true;
}

std::string App::appdir()
{
    return APPDIR;
}

std::string App::resdir()
{
    return RESDIR;
}

void App::init()
{
    // game window
    create(VideoMode::getDesktopMode(), Utilities::pickName());
    Image icon;
    icon.loadFromFile(RESDIR + "textures/icon.png");
    setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // views for window
    camera_.setSize(1920, 1080);
    camera_.setCenter(1920 / 2, 1080 / 2);
    minimap_.setSize(1920, 1080);
    minimap_.setViewport(FloatRect(0.35, 0.7, 0.28, 0.28)); // 0.03, 0.75, 0.2, 0.2

    // render textures for window
    main_texture_.create(WINDOW_SIZE.x, WINDOW_SIZE.y);
    main_texture_.setView(camera_);
    minimap_texture_.create(WINDOW_SIZE.x, WINDOW_SIZE.y);
    minimap_texture_.setView(minimap_);

    // Sprite bg;
    // bg.setTexture(resources().textures_.at(0));
    // bg.setPosition(0, 0);

    // Player player;
    // player.body.setPosition(200, 200);
    // player.body.setFillColor(Color::White);
    // player.body.setSize({40, 90});

    // itemList.push_back(gameObject{ { 0,0 }, textures.at(2), 0, 0, true, true, 0, 0 });
    // itemList.push_back(gameObject{ {0,0},{0,0} });
    // itemList.push_back(gameObject{ {0,0},{0,0} });
    // itemList.push_back(gameObject{ {0,0},{0,0} });

    // vector<gameObjectStationary> walls;
    // vector<gameObject> objects;
    // vector<Entity> entities;
    // vector<Projectile> projectiles;

    // MELEE WEAPONS
    //
    //---ID---DAMAGE---ADDITIONAL PENETRATION---SWING DELAY---HITBOX LIFETIME---HITBOX POSITIONS---HITBOX SIZE---
    //
    //  SWING DELAY - HB LIFETIME == TIME BETWEEN SWINGS ----> SWING DELAY SHOULD BE >= HB LIFETIME
    //
    //
    //  Vector2f hitboxSizeBoardStandart = { 30,25 };
    //  vector<Vector2f> hitboxesBoardStandart = { {-10,-20}, {25,-15}, {25,10}, {25,35} };
    //  Weapon board(1, 8, 1, 1, 0.7, hitboxesBoardStandart, hitboxSizeBoardStandart);

    // RANGED WEAPONS
    //
    //---ID---DAMAGE---ADDITIONAL PENETRATION---SHOT DELAY---RANGE---PROJECTILE SPEED---AMMO CAPACITY---RELOAD TIME---PROJECTILE TEXTURE---
    //
    //
    // Weapon rifle(3, 12, 1, 0.3, 600, 600, 25, 2, textures.at(2));
    // Weapon sniperRifle(4, 20, 2, 2, 800, 800, 5, 3, textures.at(2));
    // Weapon pistol(2, 8, 0, 0.5, 400, 400, 120, 1.5, textures.at(1));

    // board.actionSpriteOffset = Vector2i(10, 25);
    // board.actionSpriteSize = Vector2i(65, 85);

    // Player player{ Vector2f(20, 20), Vector2f(70, 155), textures.at(0), 6, 400 }; //speed is pixels per second
    // player.weapon = pistol;
    // player.sprite.setTexture(textures.at(0));
    // bool switchedWeapon = false;

    int currentLevel = 1;
    // levelLoad(window, objects, entities, currentLevel, 1, textures);

    bool drawMinimap = true;
    bool inMenu = true;
    bool inInventory = false;
}

void App::pollEvents()
{
    Event event;
    while (pollEvent(event))
    {
        this->event(event);

        // if (event.type == Event::KeyReleased)
        // {
        //     if (event.key.code == Keyboard::I)
        //         inInventory = true;
        // else if (event.key.code == Keyboard::Escape)
        // {
        //     float timestamp = main_clock_.getElapsedTime().asSeconds();

        //     switch (showScreenPause(window, pauseTextures, fontMain))
        //     {
        //     case -1:
        //         return -13; // window closed
        //     case 0:
        //         inMenu = true; // quit to menu
        //     case 1:
        //         break; // continue
        //         // case 2: saveLevel(currentLevel, objects, entities, textures);
        //     }
        //     // alignTime(timestamp, mainClock, player, objects, projectiles);
        // }
        // else if (event.key.code == Keyboard::E)
        // {
        // 	player.interactionFlag = true;
        // }
        // else if (event.key.code == Keyboard::R)
        // {
        // 	if (!player.isUsingWeapon)
        // 	{
        // 		if (switchedWeapon)
        // 		{
        // 			player.weapon = pistol;
        // 			switchedWeapon = false;
        // 		}
        // 		else
        // 		{
        // 			player.weapon = board;
        // 			switchedWeapon = true;
        // 		}
        // 	}
        // }
        // }
    }
}

void App::event(const Event &event)
{
    for (const auto &child : children_)
    {
        if (child->event(event))
            return;
    }

    if (event.type == Event::KeyReleased)
    {
        if (event.key.code == Keyboard::Z)
            camera_.zoom(0.5);
        else if (event.key.code == Keyboard::X)
            camera_.zoom(2);
        else if (event.key.code == Keyboard::M)
        {
        } // drawMinimap = (drawMinimap ? false : true);
        else if (event.key.code == Keyboard::Hyphen)
            minimap_.zoom(2);
        else if (event.key.code == Keyboard::Equal)
            minimap_.zoom(0.5);
        else if (event.key.code == Keyboard::Escape)
            showScreenPause(*this, resources().pause_textures_, resources().font_);
    }
    else if (event.type == Event::Closed)
        close();
}

void App::draw()
{
    for (const auto &child : children_)
        child->draw(*this);
}

void App::showMenu()
{
    auto menu = new Menu(nullptr);
    menu->setQuitFunc([this]{ close(); });
    children_.push_back(menu);
}