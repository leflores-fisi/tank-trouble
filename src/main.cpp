#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "GameController.hpp"

int main() {
    GameController *TankTrouble = new GameController();
    TankTrouble->mainLoop();
    return 0;
}
