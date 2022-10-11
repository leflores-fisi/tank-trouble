#include <iostream>
#include "Player/Bullet.hpp"
#include "Entity/Entity.hpp"

tt::Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction) :
    direction(direction),
    lifetime(sf::Clock()),
    body(sf::CircleShape(BULLET_RADIUS)),
    Entity("bullet"+std::to_string(rand())) {

    this->classList.add("bullet");
    this->body.setFillColor(sf::Color::Red);
    this->body.setPosition(position);
}
tt::Bullet::~Bullet() { }

void tt::Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->body);
}
void tt::Bullet::update(float dt) {
    if (this->getLifeTime().asSeconds() >= 2.f) {
        this->classList.add(DESTROY_CLASS);
    }
    else {
        this->velocity = this->direction * this->speed * dt;
        this->body.move(this->velocity);
    }
}
sf::Time tt::Bullet::getLifeTime() {
    return this->lifetime.getElapsedTime();
}
