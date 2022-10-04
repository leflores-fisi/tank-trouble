#pragma once
#include <SFML/Graphics.hpp>
#include "Collisions/CollisionSystem.hpp"
#include "UI/Debug.hpp"
#include "Map/Map.hpp"
#include "Player.hpp"

class GameController {
    sf::RenderWindow *window;
    sf::Event *event;
    sf::Clock clock;
    CollisionSystem collisionSystem;
    DebugUI *debugUI;
    Map *map;
    Player *player;
    float dt;

    bool isRunning();
    void handleEvents();
    void update();
    void render();
  public:
    GameController();
    ~GameController();
    void mainLoop();
};
