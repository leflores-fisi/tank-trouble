#include "CollisionSystem.hpp"
#include <cmath>
#include <iostream>

CollisionSystem::CollisionSystem()  { }
CollisionSystem::~CollisionSystem() { }

bool CollisionSystem::checkPlayerMapCollition(Player& player, std::vector<sf::RectangleShape>& walls) {
    std::vector<Collision> collisions;

    for (int i = 0; i < walls.size(); i++) {
        sf::RectangleShape expandedTarget;
        sf::RectangleShape &wall = walls[i];
        expandedTarget.setPosition(wall.getPosition() - player.getSize()/2.f);
        expandedTarget.setSize(wall.getSize() + player.getSize());

        float t;
        sf::Vector2f contact_point;
        sf::Vector2f contact_normal;
        bool collided = this->checkRayVsWallCollition(
            player.getCenterPosition(), player.getVelocity(),
            expandedTarget, t, contact_point, contact_normal
        );
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
        expandedTarget.setPosition(wall.getPosition() - player.getSize()/2.f);
        expandedTarget.setSize(wall.getSize() + player.getSize());

        float t;
        sf::Vector2f contact_point;
        sf::Vector2f contact_normal;
        bool collided = this->checkRayVsWallCollition(
            player.getCenterPosition(), player.getVelocity(),
            expandedTarget, t, contact_point, contact_normal
        );
        if (collided && !std::isnan(1-t) && t < 1 && t >= 0) {
            player.setColor(sf::Color::Magenta);
            // Resolve the collision
            sf::Vector2f resolvedVelocity = player.getVelocity();
            resolvedVelocity.x += std::abs(resolvedVelocity.x) * contact_normal.x * (1.f-t);
            resolvedVelocity.y += std::abs(resolvedVelocity.y) * contact_normal.y * (1.f-t);
            player.setVelocity(resolvedVelocity);
            hasCollided = true;
        }
    }
    if (!hasCollided) {
        player.resetColor();
    }
    return false;
}
bool CollisionSystem::checkRayVsWallCollition(sf::Vector2f rayOrigin,
                                 sf::Vector2f rayDirection,
                                 sf::RectangleShape rect,
                                 float& t_hit_near,
                                 sf::Vector2f& contact_point,
                                 sf::Vector2f& contact_normal)
{
    sf::Vector2f rectOrigin = rect.getPosition();
    sf::Vector2f rectLimit  = rect.getPosition() + rect.getSize();
    // Calculate the "time" of collision for each axis
    // Two collisions occur, "near" (first) and "far" (second)
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
