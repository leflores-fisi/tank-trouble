#pragma once
#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "map.hpp"

class Game {
    sf::RenderWindow *window;
    sf::Event *event;
    sf::Text *fpsCounter;
    sf::Font defaultFont;
    Map *map;
    Player *player;

  public:
    Game();
    ~Game();
    bool isRunning();
    void pollEvent();
    void update(float dt);
    void render(float dt);
};
