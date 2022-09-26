#pragma once
#include <SFML/Graphics.hpp>
#include "UI/Debug.hpp"
#include "Player.hpp"
#include "Map/Map.hpp"

class GameController {
    sf::RenderWindow *window;
    sf::Event *event;
    sf::Clock clock;
    DebugUI *debugUI;
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
