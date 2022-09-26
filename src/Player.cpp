#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Player.hpp"

Player::Player() :
    body(new sf::RectangleShape({ 30, 30 })),
    canon(new sf::RectangleShape({ 50, 8 })),
    velocity(150.f) {
    this->body->setFillColor(sf::Color::White);
    this->body->setPosition(100, 100);
    this->canon->setFillColor(sf::Color::Red);
}
Player::Player(sf::Vector2f position): Player() {
    this->body->setFillColor(sf::Color::White);
    this->body->setPosition(position);
    this->canon->setFillColor(sf::Color::Red);
}
Player::~Player() {
    delete this->body;
    delete this->canon;
}
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*this->body);
    target.draw(*this->canon);
}
void Player::update(float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) this->move(dt, 1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) this->rotate(dt, -1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) this->move(dt, -1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) this->rotate(dt, 1);
    this->canon->setPosition(this->body->getPosition() + sf::Vector2f(13, 13));
}
void Player::move(float dt, int dir) {
    float offsetx = this->direction.x * this->velocity*dt;
    float offsety = this->direction.y * this->velocity*dt;
    this->body->move(offsetx*dir, offsety*dir);
}
void Player::rotate(float dt, int dir) {
    float rad_angle = this->getAngle() + (dir*dt*5);
    float deg_angle = rad_angle * (180/M_PI);
    this->canon->setRotation(deg_angle);
    this->direction = sf::Vector2f(std::cos(rad_angle), std::sin(rad_angle));
}

sf::Vector2f Player::getPosition() {
    return this->body->getPosition();
}
void Player::setPosition(sf::Vector2f position) {
    this->body->setPosition(position);
}
float Player::getAngle() {
    return this->canon->getRotation() * (M_PI/180);
}
void Player::setColor(sf::Color color) {
    this->body->setFillColor(color);
}
sf::FloatRect Player::getBounds() {
    return this->body->getGlobalBounds();
}
