#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Input/Input.hpp"
#include "Player/Player.hpp"

Player::Player() :
    body(new sf::RectangleShape({ 30, 30 })),
    canon(new sf::RectangleShape({ 50, 8 })),
    velocity({ 0, 0 }),
    direction(sf::Vector2f({ 1.f, 0.f })) {

    this->body->setFillColor(sf::Color::White);
    this->body->setPosition(70.f, 70.f);
    this->canon->setFillColor(this->canonColor);
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
    for (const Bullet* b : this->bullets) {
        target.draw(*b);
    }
}
void Player::handleInput(float dt) {
    this->setVelocity({ 0, 0 });
    if (Input::isKeyPressed(sf::Keyboard::W)) this->addVelocity(dt, 1);
    if (Input::isKeyPressed(sf::Keyboard::A)) this->rotate(dt, -1);
    if (Input::isKeyPressed(sf::Keyboard::S)) this->addVelocity(dt, -1);
    if (Input::isKeyPressed(sf::Keyboard::D)) this->rotate(dt, 1);
    if (Input::isKeyPressed(sf::Keyboard::Space)) this->shoot();
}
void Player::update(float dt) {
    this->body->move(this->velocity);
    this->canon->setPosition(this->getCenterPosition());
    for (int i = 0; i < bullets.size(); i++) {
        auto &b = bullets.at(i);
        if (b->getLifeTime().asSeconds() >= 1.f) {
            delete b;
            this->bullets.erase(this->bullets.begin() + i);
        }
        else b->update(dt);
    }
}
bool Player::shoot() {
    if (this->bullets.size() >= 1) return false;
    sf::Vector2f muzzle = this->getCenterPosition() + this->direction * canon->getSize().x;
    Bullet* b = new Bullet(muzzle, this->direction);
    this->bullets.push_back(b);
    return true;
}
void Player::addVelocity(float dt, int dir) {
    float offsetx = this->direction.x * VEL * dt;
    float offsety = this->direction.y * VEL * dt;
    this->velocity = { offsetx*dir, offsety*dir };
}
void Player::rotate(float dt, int dir) {
    float rad_angle = this->getAngle() + (dir*dt*5);
    float deg_angle = rad_angle * (180/M_PI);
    this->canon->setRotation(deg_angle);
    // Save the direction of the canon
    this->direction.x = std::cos(rad_angle);
    this->direction.y = std::sin(rad_angle);
}

// Setters 🐢
void Player::setColor(sf::Color color) { this->body->setFillColor(color); }
void Player::resetColor() { this->setColor(this->bodyColor); }
void Player::setVelocity(sf::Vector2f vel) {
    this->velocity.x = vel.x;
    this->velocity.y = vel.y;
}
// Getters 🐢
float        Player::getAngle() {return this->canon->getRotation() * (M_PI/180); }
sf::Vector2f Player::getSize() { return this->body->getSize(); }
sf::Vector2f Player::getVelocity() { return this->velocity; }
sf::Vector2f Player::getPosition() { return this->body->getPosition(); }
sf::Vector2f Player::getCenterPosition() {
    return this->body->getPosition() + this->getSize()/2.f;
}
