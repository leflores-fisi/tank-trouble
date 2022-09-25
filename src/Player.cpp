#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Player.hpp"

Player::Player() :
    body(new sf::RectangleShape({ 30, 30 })),
    canon(new sf::RectangleShape({ 50, 8 })),
    angle(0), velocity(150.f) {
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
void Player::move(float dt, int direction) {
    float offsetx = cos(this->getAngle())*this->velocity*dt;
    float offsety = sin(this->getAngle())*this->velocity*dt;
    this->body->move(direction*offsetx, direction*offsety);
}
void Player::rotate(float dt, int direction) {
    this->angle += dt*direction * 5;
    this->canon->setRotation(this->angle* (180/M_PI));
}

sf::Vector2f Player::getPosition() { return this->body->getPosition(); }
void Player::setPosition(sf::Vector2f position) { this->body->setPosition(position); }
float Player::getAngle() { return this->canon->getRotation()*M_PI/180; }

void Player::setColor(sf::Color color) { this->body->setFillColor(color); }
sf::FloatRect Player::getBounds() { return this->body->getGlobalBounds(); }
