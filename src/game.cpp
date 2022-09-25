#include <iostream>
#include "game.hpp"

Game::Game() :
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

Game::~Game() {
    delete this->window;
    delete this->event;
    delete this->player;
    delete this->map;
    delete this->fpsCounter;
}
bool Game::isRunning() {
    return this->window->isOpen();
}
void Game::pollEvent() {
    while (this->window->pollEvent(*(this->event))) {

        if (this->event->type == sf::Event::Closed) this->window->close();

        if (this->event->type == sf::Event::Resized) {
            this->window->setView(sf::View(sf::FloatRect(0, 0, this->event->size.width, this->event->size.height)));
            std::cout << "New size: " << this->event->size.width << "x" << this->event->size.height << std::endl;
        }
    }
}
void Game::update(float dt) {
    this->pollEvent();
    this->fpsCounter->setString(std::to_string(1.f/dt) + " fps");
    this->player->update(dt);
}
void Game::render() {
    this->window->clear(sf::Color::Black);
    // Map
    this->map->draw(*this->window);
    // Entities
    this->player->draw(*this->window);
    // UI
    this->window->draw(*this->fpsCounter);
    this->window->display();
}
