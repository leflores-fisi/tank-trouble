#include "Player/Bullet.hpp"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction) :
    direction(direction),
    body(sf::RectangleShape({ 5.f, 5.f })) {
    this->body.setFillColor(sf::Color::Red);
    this->body.setPosition(position);
}
Bullet::~Bullet() {}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->body);
}
void Bullet::update(float dt) {
    this->velocity = this->direction * 250.f * dt;
    this->body.move(this->velocity);
}
