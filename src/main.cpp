#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "game.hpp"

int main() {
    Game *game = new Game();
    //window.setFramerateLimit(10);

    sf::Clock clock;
    while (game->isRunning()) {
        float dt = clock.restart().asSeconds();
        game->update(dt);
        game->render(dt);
    }
    return 0;
}
