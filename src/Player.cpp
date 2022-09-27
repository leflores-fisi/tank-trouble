#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Player.hpp"

Player::Player() :
    body(new sf::RectangleShape({ 30, 30 })),
    canon(new sf::RectangleShape({ 50, 8 })),
    canonRay(sf::VertexArray(sf::Lines)),
    velocity(150.f),
    direction(sf::Vector2f({ 1.f, 0.f })) {

    this->body->setFillColor(sf::Color::White);
    this->body->setPosition(100, 100);
    this->canon->setFillColor(this->canonColor);
    this->canonRay.append(sf::Vertex(this->body->getPosition() + sf::Vector2f(13, 13)));
    this->canonRay.append(sf::Vertex(this->canonRay[0].position + this->direction*this->velocity));
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
    target.draw(this->canonRay);
}
void Player::update(float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) this->move(dt, 1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) this->rotate(dt, -1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) this->move(dt, -1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) this->rotate(dt, 1);
    this->canon->setPosition(this->body->getPosition() + sf::Vector2f(11, 11));
    this->canonRay[0].position = this->canon->getPosition();
    this->canonRay[1].position = this->canon->getPosition() + this->direction*this->velocity*dt;
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
    // Save the direction of the canon
    this->direction.x = std::cos(rad_angle);
    this->direction.y = std::sin(rad_angle);
}

// Axis-Aligned Bounding Box (AABB) collision detection
bool Player::checkRayVsWallCollition(sf::Vector2f rayOrigin,
                                     sf::Vector2f rayDirection,
                                     sf::RectangleShape rect) {
    sf::Vector2f rectOrigin = rect.getPosition();
    sf::Vector2f rectLimit  = rect.getPosition() + rect.getSize();
    float t_nearx = (rectOrigin.x - rayOrigin.x) / rayDirection.x;
    float t_neary = (rectOrigin.y - rayOrigin.y) / rayDirection.y;
    float t_farx  = (rectLimit.x  - rayOrigin.x) / rayDirection.x;
    float t_fary  = (rectLimit.y  - rayOrigin.y) / rayDirection.y;
    
    if (t_nearx > t_farx) std::swap(t_nearx, t_farx);
    if (t_neary > t_fary) std::swap(t_neary, t_fary);

    bool hasCollided = (t_nearx < t_fary && t_neary < t_farx);
    if (!hasCollided) return false;

    float t_hit_near = std::max(t_nearx, t_neary);
    float t_hit_far = std::min(t_farx, t_fary);

    if (t_hit_near < 0) {
        if (t_hit_far < 0) return false;
        t_hit_near = t_hit_far;
    }
    return true;
}

bool Player::checkCollisionForMap(std::vector<sf::RectangleShape>& walls) {
    // Store mouse coordinates
    sf::Vector2f origin = this->canonRay[0].position;
    sf::Vector2f head = this->canonRay[1].position;
    bool hasCollided = false;

    for (auto& wall : walls) {
        if (checkRayVsWallCollition(origin, head - origin, wall)) {
            this->setColor(sf::Color::Magenta);
            wall.setFillColor(sf::Color::Red);
            hasCollided = true;
        }
        else wall.setFillColor(sf::Color::White);
    }
    if (!hasCollided) this->setColor(this->bodyColor);
    return false;
}

float Player::getAngle() {
    return this->canon->getRotation() * (M_PI/180);
}
void Player::setColor(sf::Color color) {
    this->body->setFillColor(color);
}
