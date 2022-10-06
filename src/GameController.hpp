#pragma once
#include <SFML/Graphics.hpp>
#include "Collisions/CollisionSystem.hpp"
#include "UI/Debug.hpp"
#include "Map/Map.hpp"
#include "Player/Player.hpp"

class GameController {
    sf::RenderWindow *window;
    Map     *map;
    Player  *player;
    DebugUI *debugUI;
    sf::Event event;
    sf::Clock clock;
    CollisionSystem collisionSystem;
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
