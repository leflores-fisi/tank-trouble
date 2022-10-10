#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Input/Input.hpp"
#include "Player/Player.hpp"

#define CANON_LENGTH 30.f
#define CANON_WIDTH 12.f

tt::Player::Player() :
    body(new sf::RectangleShape()),
    canon(new sf::RectangleShape({ CANON_LENGTH, CANON_WIDTH })),
    velocity({ 0, 0 }),
    direction(sf::Vector2f({ 1.f, 0.f })) {

    this->id = "player1";
    this->classList.add("player");
    std::cout << "Player created" << std::endl;
    this->body->setSize({ this->size, this->size });
    this->body->setFillColor(sf::Color::White);
    this->body->setPosition(70.f, 70.f);
    this->canon->setFillColor(this->canonColor);
    this->canon->setOrigin(-2.f, CANON_WIDTH/2);
}
tt::Player::Player(sf::Vector2f position): Player() {
    this->body->setFillColor(sf::Color::White);
    this->body->setPosition(position);
    this->canon->setFillColor(sf::Color::Red);
}
tt::Player::~Player() {
    delete this->body;
    delete this->canon;
}
void tt::Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*this->body);
    target.draw(*this->canon);
    for (const tt::Bullet* b : this->bullets) {
        target.draw(*b);
    }
}
void tt::Player::handleInput(float dt) {
    this->setVelocity({ 0, 0 });
    if (tt::Input::isKeyPressed(sf::Keyboard::W)) this->addVelocity(dt, 1);
    if (tt::Input::isKeyPressed(sf::Keyboard::A)) this->rotate(dt, -1);
    if (tt::Input::isKeyPressed(sf::Keyboard::S)) this->addVelocity(dt, -1);
    if (tt::Input::isKeyPressed(sf::Keyboard::D)) this->rotate(dt, 1);
    if (tt::Input::isKeyPressed(sf::Keyboard::Space)) this->shoot();
}
void tt::Player::update(float dt) {
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
bool tt::Player::shoot() {
    if (this->bullets.size() >= 1) return false;
    sf::Vector2f muzzle = this->getCenterPosition() + this->direction * canon->getSize().x;
    Bullet* b = new Bullet(muzzle, this->direction);
    this->bullets.push_back(b);
    return true;
}
void tt::Player::addVelocity(float dt, int dir) {
    float offsetx = this->direction.x * VEL * dt;
    float offsety = this->direction.y * VEL * dt;
    this->velocity = { offsetx*dir, offsety*dir };
}
void tt::Player::rotate(float dt, int dir) {
    float rad_angle = this->getAngle() + (dir*dt*5);
    float deg_angle = rad_angle * (180/M_PI);
    this->canon->setRotation(deg_angle);
    // Save the direction of the canon
    this->direction.x = std::cos(rad_angle);
    this->direction.y = std::sin(rad_angle);
}

// Setters 🐢
void tt::Player::setColor(sf::Color color) { this->body->setFillColor(color); }
void tt::Player::resetColor() { this->setColor(this->bodyColor); }
void tt::Player::setVelocity(sf::Vector2f vel) {
    this->velocity.x = vel.x;
    this->velocity.y = vel.y;
}
// Getters 🐢
float        tt::Player::getAngle() {return this->canon->getRotation() * (M_PI/180); }
sf::Vector2f tt::Player::getSize() { return this->body->getSize(); }
sf::Vector2f tt::Player::getVelocity() { return this->velocity; }
sf::Vector2f tt::Player::getPosition() { return this->body->getPosition(); }
sf::Vector2f tt::Player::getCenterPosition() {
    return this->body->getPosition() + this->getSize()/2.f;
}
