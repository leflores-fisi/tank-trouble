#include <iostream>
#include "Player/Bullet.hpp"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction) :
    direction(direction),
    lifetime(sf::Clock()),
    body(sf::RectangleShape({ 10.f, 10.f })) {
    this->body.setFillColor(sf::Color::Red);
    this->body.setPosition(position);
}
Bullet::~Bullet() { }

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->body);
}
void Bullet::update(float dt) {
    this->velocity = this->direction * this->speed * dt;
    this->body.move(this->velocity);
}
sf::Time Bullet::getLifeTime() {
    return this->lifetime.getElapsedTime();
}
