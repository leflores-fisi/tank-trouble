#include <iostream>
#include "Player/Bullet.hpp"
#include "Player/Player.hpp"
#include "Entity/Entity.hpp"
#include "Entity/EntityManager.hpp"

tt::Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction) :
    direction(direction),
    lifetime(sf::Clock()),
    body(sf::CircleShape(BULLET_RADIUS)),
    Entity("bullet"+std::to_string(rand())) {

    this->classList.add("bullet");
    this->velocityLine.append(sf::Vertex(position, sf::Color::Red));
    this->velocityLine.append(sf::Vertex(position + sf::Vector2f({10.f, 10.f}), sf::Color::Red));
    this->body.setFillColor(sf::Color::Red);
    this->body.setPosition(position);
}
tt::Bullet::~Bullet() { }

void tt::Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->body);
    target.draw(this->velocityLine);
}
void tt::Bullet::update(float dt) {
    if (this->getLifeTime().asSeconds() >= 10.f) {
        this->classList.add(DESTROY_CLASS);
        return;
    }
    // The velocity is calculated and resolved in tt::CollisionSystem::checkBulletMapCollision
    this->body.move(this->velocity);
    this->velocityLine[0].position = this->getCenterPosition();
    this->velocityLine[1].position = this->getCenterPosition() + this->velocity;
    for (auto p : tt::EntityManager::querySelectorAll(".player")) {
        tt::Player* player = dynamic_cast<tt::Player*>(p);

        if (player->body->getGlobalBounds().intersects(this->body.getGlobalBounds())) {
            std::cout << "Hit player " << player->id << std::endl;
        }
    }
}
void tt::Bullet::calculateVelocity(float dt) {
    this->velocity = this->direction * this->speed * dt;
    // std::cout << "Bullet: " << this->id << " velocity: " << this->velocity.x << ", " << this->velocity.y << std::endl;
}
sf::Time tt::Bullet::getLifeTime() {
    return this->lifetime.getElapsedTime();
}
sf::Vector2f tt::Bullet::getSize() {
    return sf::Vector2f(BULLET_RADIUS * 2, BULLET_RADIUS * 2);
}

sf::Vector2f tt::Bullet::getDirection() {
    return this->direction;
}
void tt::Bullet::setDirection(sf::Vector2f dir) {
    this->direction = dir;
}
sf::Vector2f tt::Bullet::getVelocity() {
    return this->velocity;
}
void tt::Bullet::setVelocity(sf::Vector2f vel) {
    this->velocity = vel;
}
sf::Vector2f tt::Bullet::getCenterPosition() {
    return this->body.getPosition() + sf::Vector2f(BULLET_RADIUS, BULLET_RADIUS);
}
sf::Vector2f tt::Bullet::getPosition() {
    return this->body.getPosition();
}
void tt::Bullet::setPosition(sf::Vector2f pos) {
    this->body.setPosition(pos);
}
