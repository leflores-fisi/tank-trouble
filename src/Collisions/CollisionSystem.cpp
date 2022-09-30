#include "CollisionSystem.hpp"
#include <cmath>
#include <iostream>

CollisionSystem::CollisionSystem()  { }
CollisionSystem::~CollisionSystem() { }

void CollisionSystem::resolvePlayerCollision(Player& player, CollisionSystem::CollisionInfo info) {
    sf::Vector2f resolvedVelocity = player.getVelocity();

    resolvedVelocity.x += std::abs(resolvedVelocity.x) * info.contactNormal.x * (1.f-info.t_hit);
    resolvedVelocity.y += std::abs(resolvedVelocity.y) * info.contactNormal.y * (1.f-info.t_hit);
    player.setVelocity(resolvedVelocity);
}

bool CollisionSystem::checkPlayerMapCollision(Player& player, std::vector<sf::RectangleShape>& walls) {

    std::vector<CollisionInfo> collisions;

    bool hasCollided = false;
    for (int i = 0; i < walls.size(); i++) {
        sf::RectangleShape &wall = walls[i];

        sf::RectangleShape expandedTarget;
        expandedTarget.setPosition(wall.getPosition() - player.getSize()/2.f);
        expandedTarget.setSize(wall.getSize() + player.getSize());

        CollisionInfo info_ref;
        bool collided = this->checkRayVsWallCollision(
            player.getCenterPosition(),
            player.getVelocity(),
            expandedTarget,
            info_ref
        );
        if (collided) {
            info_ref.index = i;
            collisions.push_back(info_ref);
            wall.setFillColor(sf::Color::Red);
            hasCollided = true;
        }
        else {
            wall.setFillColor(sf::Color(87, 104, 191));
        }
    }
    if (!hasCollided) player.resetColor();
    else player.setColor(sf::Color::Magenta);

    // Sort the collisions by the time proximity
    std::sort(collisions.begin(), collisions.end(), [](CollisionInfo &a, CollisionInfo &b) {
        return a.t_hit < b.t_hit;
    });
    for (const CollisionInfo &collision : collisions) {
            this->resolvePlayerCollision(player, collision);

    }
    return hasCollided;
}

bool CollisionSystem::checkRayVsWallCollision
    (sf::Vector2f rayOrigin, sf::Vector2f rayDirection, sf::RectangleShape rect, CollisionSystem::CollisionInfo& info) {

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
    info.t_hit       = std::max(t_nearx, t_neary); // First collision
    float t_hit_far  = std::min(t_farx, t_fary);   // Second collision

    // t_far < 0 means that the target is opposite to the ray
    if (t_hit_far < 0) return false;
    if (info.t_hit >= 1.f || info.t_hit < 0) return false;

    // The "t" value is such that:
    // contactPoint = rayOrigin + t_hit*rayDirection;

    info.contactNormal = { 0, 0 };
    if (t_nearx > t_neary) {
        if (rayDirection.x < 0) info.contactNormal.x = 1.f;
        else info.contactNormal.x = -1.f;
    }
    else {
        if (rayDirection.y < 0) info.contactNormal.y = 1.f;
        else info.contactNormal.y = -1.f;
    }
    return true;
}
