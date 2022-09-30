#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Player.hpp"

// Note: canonRay is now only a visual representation of the velocity vector,
//       it is not used for collision detection

Player::Player() :
    body(new sf::RectangleShape({ 30, 30 })),
    canon(new sf::RectangleShape({ 50, 8 })),
    canonRay(sf::VertexArray(sf::Lines)),
    velocity({ 0, 0 }),
    direction(sf::Vector2f({ 1.f, 0.f })) {

    this->body->setFillColor(sf::Color::White);
    this->body->setPosition(70.f, 70.f);
    this->canon->setFillColor(this->canonColor);
    this->canonRay.append(sf::Vertex(this->body->getPosition()));
    this->canonRay.append(sf::Vertex(this->canonRay[0].position + this->velocity*VEL));
    // Set canon color
    this->canonRay[0].color = sf::Color::Black;
    this->canonRay[1].color = sf::Color::Black;
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
void Player::update(float dt, std::vector<sf::RectangleShape> &walls) {
    this->velocity = { 0, 0 };
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) this->addVelocity(dt, 1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) this->rotate(dt, -1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) this->addVelocity(dt, -1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) this->rotate(dt, 1);
    this->checkCollisionForMap(walls);
    this->updatePosition();
}
void Player::addVelocity(float dt, int dir) {
    float offsetx = this->direction.x * VEL * dt;
    float offsety = this->direction.y * VEL * dt;
    this->velocity = { offsetx*dir, offsety*dir };
}
void Player::updatePosition() {
    this->body->move(this->velocity);
    this->canon->setPosition(this->body->getPosition() + this->body->getSize() / 2.f);
    this->canonRay[0].position = this->canon->getPosition();
    this->canonRay[1].position = this->canon->getPosition() + this->velocity;
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
                                     sf::RectangleShape rect,
                                     float& t_hit_near,
                                     sf::Vector2f& contact_point,
                                     sf::Vector2f& contact_normal) {
    sf::Vector2f rectOrigin = rect.getPosition();
    sf::Vector2f rectLimit  = rect.getPosition() + rect.getSize();
    // Calculate the "time" of collision for each axis
    // Two collisions occur, "near" (first) and "far" (second)
    if (velocity == sf::Vector2f(0, 0)) return false;
    float t_nearx = (rectOrigin.x - rayOrigin.x) / rayDirection.x;
    float t_neary = (rectOrigin.y - rayOrigin.y) / rayDirection.y;
    float t_farx  = (rectLimit.x  - rayOrigin.x) / rayDirection.x;
    float t_fary  = (rectLimit.y  - rayOrigin.y) / rayDirection.y;

    if (std::isnan(t_nearx) || std::isnan(t_neary)) return false;
    if (std::isnan(t_farx)  || std::isnan(t_fary )) return false;

    // Swap the values properly (if the ray is in the opposite direction)
    if (t_nearx > t_farx) std::swap(t_nearx, t_farx);
    if (t_neary > t_fary) std::swap(t_neary, t_fary);

    // Early rejection
    bool hasCollided = (t_nearx <= t_fary && t_neary <= t_farx);
    if (!hasCollided) return false;

    // Save the "time" for our two collisions
    t_hit_near = std::max(t_nearx, t_neary); // First collision
    float t_hit_far  = std::min(t_farx, t_fary);   // Second collision

    // t_far < 0 means that the target is opposite to the ray
    if (t_hit_far < 0) return false;
    // if (t_hit_near >= 1.f || t_hit_near < 0) return false;

    // The "t" value is such that:
    contact_point = rayOrigin + t_hit_near*rayDirection;
    contact_normal = { 0, 0 };

    if (t_nearx > t_neary) {
        if (rayDirection.x < 0) contact_normal.x = 1.f;
        else contact_normal.x = -1.f;
    }
    else {
        if (rayDirection.y < 0) contact_normal.y = 1.f;
        else contact_normal.y = -1.f;
    }
    return true;
}

struct Collision {
    int index;
    float t_hit_near;
};

bool Player::checkCollisionForMap(std::vector<sf::RectangleShape>& walls) {

    std::vector<Collision> collisions;
    sf::Vector2f origin = this->canon->getPosition();
    // if (this->velocity == sf::Vector2f(0, 0)) return false;

    for (int i = 0; i < walls.size(); i++) {
        sf::RectangleShape expandedTarget;
        sf::RectangleShape &wall = walls[i];
        expandedTarget.setPosition(wall.getPosition() - this->body->getSize()/2.f);
        expandedTarget.setSize(wall.getSize() + this->body->getSize());

        float t;
        sf::Vector2f contact_point;
        sf::Vector2f contact_normal;
        bool collided = this->checkRayVsWallCollition(origin, this->velocity, expandedTarget, t, contact_point, contact_normal);
        if (collided && t >= 0 && t < 1) {
            Collision c;
            c.index = i;
            c.t_hit_near = t;
            collisions.push_back(c);
            wall.setFillColor(sf::Color::Red);
        }
        else {
            wall.setFillColor(sf::Color(87, 104, 191));
        }
    }

    // Sort the collisions by the time proximity
    std::sort(collisions.begin(), collisions.end(), [](Collision &a, Collision &b) {
        return a.t_hit_near < b.t_hit_near;
    });

    bool hasCollided = false;
    for (const Collision &c : collisions) {
        sf::RectangleShape expandedTarget;
        sf::RectangleShape &wall = walls[c.index];
        expandedTarget.setPosition(wall.getPosition() - this->body->getSize()/2.f);
        expandedTarget.setSize(wall.getSize() + this->body->getSize());

        float t;
        sf::Vector2f contact_point;
        sf::Vector2f contact_normal;
        bool collided = this->checkRayVsWallCollition(origin, this->velocity, expandedTarget, t, contact_point, contact_normal);
        if (collided && !std::isnan(1-t) && t < 1 && t >= 0) {
            this->setColor(sf::Color::Magenta);
            // Resolve the collision
            this->velocity.x = this->velocity.x + std::abs(this->velocity.x) * contact_normal.x * (1.f-t);
            this->velocity.y = this->velocity.y + std::abs(this->velocity.y) * contact_normal.y * (1.f-t);
            hasCollided = true;
        }
        // else wall.setFillColor(sf::Color(87, 104, 191));
    }
    if (!hasCollided) {
        this->setColor(this->bodyColor);
    }
    return false;
}

float Player::getAngle() {
    return this->canon->getRotation() * (M_PI/180);
}
void Player::setColor(sf::Color color) {
    this->body->setFillColor(color);
}
