#include <iostream>
#include "GameController.hpp"

void GameController::mainLoop() {
    while (this->isRunning()) {
        float dt = this->clock.restart().asSeconds();
        this->update(dt);
        this->render();
    }
}

GameController::GameController() :
    window(new sf::RenderWindow(sf::VideoMode(800, 600), "Tank trouble")),
    event(new sf::Event()),
    player(new Player({ 100, 100 })),
    map(new Map()),
    fpsCounter(new sf::Text()),
    defaultFont(sf::Font()) {

    if (!this->defaultFont.loadFromFile("static/caskaydiaNF.ttf")) {
        std::cout << "Cant load default font" << std::endl;
    }
    this->fpsCounter->setFont(this->defaultFont);
    this->fpsCounter->setCharacterSize(16);
    this->fpsCounter->setFillColor(sf::Color::White);
    this->map->load("static/maps/map.txt");
    std::cout << "Succesfully loaded" << std::endl;
}

GameController::~GameController() {
    delete this->window;
    delete this->event;
    delete this->player;
    delete this->map;
    delete this->fpsCounter;
}
bool GameController::isRunning() {
    return this->window->isOpen();
}
void GameController::pollEvent() {
    while (this->window->pollEvent(*(this->event))) {
        sf::Event::EventType type = this->event->type;

        if (type == sf::Event::Closed) {
            this->window->close();
        }
        if (type == sf::Event::Resized) {
            unsigned int width = this->event->size.width;
            unsigned int height = this->event->size.height;

            this->window->setView(sf::View(sf::FloatRect(0, 0, width, height)));
            std::cout << "New size: " << width << "x" << height << std::endl;
        }
    }
}
void GameController::update(float dt) {
    this->pollEvent();
    this->fpsCounter->setString(std::to_string(1.f/dt) + " fps");
    this->player->update(dt);
}
void GameController::render() {
    this->window->clear(sf::Color::Black);
    // Map
    this->map->draw(*this->window);
    // Entities
    this->player->draw(*this->window);
    // UI
    this->window->draw(*this->fpsCounter);
    this->window->display();
}
