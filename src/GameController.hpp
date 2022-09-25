#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Map.hpp"

class GameController {
    sf::RenderWindow *window;
    sf::Event *event;
    sf::Text *fpsCounter;
    sf::Font defaultFont;
    sf::Clock clock;
    Map *map;
    Player *player;

    bool isRunning();
    void pollEvent();
    void update(float dt);
    void render();
  public:
    GameController();
    ~GameController();
    void mainLoop();
};