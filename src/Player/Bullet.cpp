#include <iostream>
#include "Player/Bullet.hpp"

tt::Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction) :
    direction(direction),
    lifetime(sf::Clock()),
    body(sf::RectangleShape({ 10.f, 10.f })) {
    this->body.setFillColor(sf::Color::Red);
    this->body.setPosition(position);
}
tt::Bullet::~Bullet() { }

void tt::Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->body);
}
void tt::Bullet::update(float dt) {
    this->velocity = this->direction * this->speed * dt;
    this->body.move(this->velocity);
}
sf::Time tt::Bullet::getLifeTime() {
    return this->lifetime.getElapsedTime();
}
