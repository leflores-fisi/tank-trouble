#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "GameController.hpp"

int main(void) {
    tt::GameController *TankTrouble = new tt::GameController();
    TankTrouble->mainLoop();
    return 0;
}
