#pragma once
#include <SFML/Graphics.hpp>
#include "Collisions/CollisionSystem.hpp"
#include "UI/Debug.hpp"
#include "Map/Map.hpp"
#include "Player/Player.hpp"

namespace tt {

class GameController {
    sf::RenderWindow *window;
    tt::Map     *map;
    tt::DebugUI *debugUI;
    sf::Event event;
    sf::Clock clock;
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
}
