#include "GameController.hpp"

int main(void) {
    tt::GameController *TankTrouble = new tt::GameController();
    TankTrouble->mainLoop();

    delete TankTrouble;
    return 0;
}
