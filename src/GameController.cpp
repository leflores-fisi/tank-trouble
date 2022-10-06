#include <iostream>
#include "GameController.hpp"
#include "Input/Input.hpp"

GameController::GameController() :
    window(new sf::RenderWindow(sf::VideoMode(800, 600), "Tank trouble")),
    player(new Player({ 190.f, 190.f })),
    event(sf::Event()),
    map(new Map()),
    debugUI(new DebugUI()) {

    Input::setup();
    this->window->setKeyRepeatEnabled(false);
    this->map->load("static/maps/map.txt");
}
GameController::~GameController() {
    delete this->window;
    delete this->player;
    delete this->map;
}

void GameController::mainLoop() {
    while (this->isRunning()) {
        this->dt = this->clock.restart().asSeconds();
        this->update();
        this->render();
    }
}
void GameController::update() {
    DebugUI::DebugInfo info;
    info.deltaTime = std::to_string(1.f/this->dt);
    this->debugUI->update(info);

    // First, check input and handle events
    this->handleEvents();

    // Then, properly manage those events
    collisionSystem.checkPlayerMapCollision(
        *this->player,
        *this->map->getWalls()
    );
    this->player->update(this->dt);
}
void GameController::handleEvents() {
    while (this->window->pollEvent(this->event)) {
        sf::Event::EventType type = this->event.type;

        if (type == sf::Event::Closed) {
            this->window->close();
        }
        if (type == sf::Event::Resized) {
            unsigned int width  = this->event.size.width;
            unsigned int height = this->event.size.height;

            this->window->setView(sf::View(sf::FloatRect(0, 0, width, height)));
            std::cout << "New size: " << width << "x" << height << std::endl;
        }

        if (!this->window->hasFocus()) continue;
        if (type == sf::Event::KeyPressed || type == sf::Event::KeyReleased) {
            Input::pushKeyEvent(this->event);
        }
        if (type == sf::Event::MouseButtonPressed || type == sf::Event::MouseButtonReleased) {
            Input::pushMouseEvent(this->event);
        }
    }
    this->player->handleInput(this->dt);
}
void GameController::render() {
    this->window->clear(sf::Color::Black);
    // Map
    this->window->draw(*this->map);
    // Entities
    this->window->draw(*this->player);
    // UI
    this->window->draw(*this->debugUI);
    this->window->display();
}
bool GameController::isRunning() {
    return this->window->isOpen();
}
