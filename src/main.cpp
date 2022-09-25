#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "game.hpp"

int main() {
    Game *TankTrouble = new Game();

    sf::Clock clock;
    while (TankTrouble->isRunning()) {
        float dt = clock.restart().asSeconds();
        TankTrouble->update(dt);
        TankTrouble->render();
    }
    return 0;
}
