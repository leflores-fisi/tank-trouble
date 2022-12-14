#include <iostream>
#include "GameController/GameController.hpp"
#include "Entity/EntityManager.hpp"
#include "Input/Input.hpp"

// TODO:
// - Documentate code
// - Bullets collision

tt::GameController::GameController() :
    window(new sf::RenderWindow(sf::VideoMode(800, 600), "Tank trouble")),
    event(sf::Event()),
    map(new Map()),
    debugUI(new DebugUI()) {

    Input::setup(*this->window);
    this->map->load("static/maps/map.txt");
    tt::EntityManager::instantiate(new Player("player1", { 170.f, 170.f }, {
        sf::Keyboard::W,
        sf::Keyboard::A,
        sf::Keyboard::S,
        sf::Keyboard::D,
        sf::Keyboard::Q
    }));
    tt::EntityManager::instantiate(new Player("player2", { 950.f, 550.f }, {
        sf::Keyboard::Up,
        sf::Keyboard::Left,
        sf::Keyboard::Down,
        sf::Keyboard::Right,
        sf::Keyboard::P
    }));
}
tt::GameController::~GameController() {
    delete this->window;
    delete this->debugUI;
    delete this->map;
    tt::EntityManager::deleteALlEntities();
}

void tt::GameController::mainLoop() {
    while (this->isRunning()) {
        this->dt = this->clock.restart().asSeconds();
        this->update();
        this->render();
    }
}
void tt::GameController::update() {
    DebugUI::DebugInfo info; // TODO: move this down
    info.fpsCount = std::to_string(1.f/this->dt);
    info.entityCount = std::to_string(tt::EntityManager::entityCount());
    this->debugUI->update(info);

    // First, check input and handle events
    this->handleEvents();

    // Then, properly manage those events
    for (int i = 0; i < tt::EntityManager::entityCount(); i++) {
        tt::Entity* e = tt::EntityManager::entities.at(i);

        if (e->classList.contains(DESTROY_CLASS)) {
            tt::EntityManager::deleteEntity(e->id);
            continue;
        }
        if (e->classList.contains("player")) {
            tt::Player* player = dynamic_cast<Player*>(e);
            tt::CollisionSystem::checkPlayerMapCollision(
                *player,
                *this->map->getWalls()
            );
        }
        if (e->classList.contains("bullet")) {
            tt::Bullet* bullet = dynamic_cast<tt::Bullet*>(e);
            bullet->calculateVelocity(this->dt);
            tt::CollisionSystem::checkBulletMapCollision(
                *bullet,
                *this->map->getWalls()
            );
        }
        e->update(this->dt);
    }
}
void tt::GameController::handleEvents() {
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

        if (type == sf::Event::KeyPressed || type == sf::Event::KeyReleased) {
            Input::pushKeyEvent(this->event);

            if (this->event.key.code == sf::Keyboard::K) {
                tt::EntityManager::deleteALlEntities();
            }
        }
        if (type == sf::Event::MouseButtonPressed || type == sf::Event::MouseButtonReleased) {
            Input::pushMouseEvent(this->event);
        }
    }
    auto players = tt::EntityManager::querySelectorAll(".player");
    for (const auto &p : players) {
        auto pl = dynamic_cast<Player*>(p);
        pl->handleInput(this->dt);
    }
}
void tt::GameController::render() {
    this->window->clear(sf::Color::Black);

    // Map
    this->window->draw(*this->map);
    // Entities
    for (const tt::Entity* e : tt::EntityManager::entities) {
        this->window->draw(*e);
    }
    // UI
    this->window->draw(*this->debugUI);
    this->window->display();
}
bool tt::GameController::isRunning() {
    return this->window->isOpen();
}
