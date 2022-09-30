#include "CollisionSystem.hpp"
#include <cmath>
#include <iostream>

CollisionSystem::CollisionSystem()  { }
CollisionSystem::~CollisionSystem() { }

void CollisionSystem::resolvePlayerCollision(
    Player& player,
    CollisionSystem::CollisionInfo info
) {
    sf::Vector2f resolvedVelocity = player.getVelocity();

    resolvedVelocity.x += std::abs(resolvedVelocity.x) * info.contactNormal.x * (1.f-info.time);
    resolvedVelocity.y += std::abs(resolvedVelocity.y) * info.contactNormal.y * (1.f-info.time);
    player.setVelocity(resolvedVelocity);
}

bool CollisionSystem::checkPlayerMapCollision(
    Player& player,
    std::vector<sf::RectangleShape>& walls
) {

    std::vector<CollisionLog> collisionsLog;

    bool hasCollided = false;
    for (int i = 0; i < walls.size(); i++) {
        sf::RectangleShape &wall = walls[i];
        CollisionLog collision;

        collision.time = this->getRayCollisionTime(
            player.getCenterPosition(),
            player.getVelocity(),
            player.getSize(),
            wall
        );
        if (collision.time >= 0.f && collision.time < 1.f) {
            collision.index = i;
            collisionsLog.push_back(collision);
            wall.setFillColor(sf::Color::Red);
            hasCollided = true;
        }
        else wall.setFillColor(sf::Color(87, 104, 191));
    }
    // Sort the collisions by the time proximity
    std::sort(collisionsLog.begin(), collisionsLog.end(),
        [](CollisionLog &a, CollisionLog &b) {
            return a.time < b.time;
        }
    );
    for (const CollisionLog &collision : collisionsLog) {
        CollisionInfo collisionInfo;
        sf::RectangleShape &wall = walls.at(collision.index);

        this->checkRayVsWallCollision(
            player.getCenterPosition(),
            player.getVelocity(),
            player.getSize(),
            wall,
            collisionInfo
        );
        this->resolvePlayerCollision(player, collisionInfo);
    }

    if (!hasCollided) player.resetColor();
    else player.setColor(sf::Color::Magenta);
    return hasCollided;
}

// Note:
// I know this logic is repeated at CollisionSystem::checkRayVsWallCollision
// but the collition must be recalculated
// this is because as we are resolving collisions, the player's velocity changes
float CollisionSystem::getRayCollisionTime(
    sf::Vector2f rayOrigin,
    sf::Vector2f rayDirection,
    sf::Vector2f playerSize,
    sf::RectangleShape rect
) {

    // Expand the rect bounds to include the player size
    sf::RectangleShape target;
    target.setPosition(rect.getPosition() - playerSize/2.f);
    target.setSize(rect.getSize() + playerSize);

    sf::Vector2f rectOrigin = target.getPosition();
    sf::Vector2f rectLimit  = target.getPosition() + target.getSize();

    // Calculate the "time" of collision for each axis
    // Two collisions occur, "near" (first) and "far" (second)
    float t_nearx = (rectOrigin.x - rayOrigin.x) / rayDirection.x;
    float t_neary = (rectOrigin.y - rayOrigin.y) / rayDirection.y;
    float t_farx  = (rectLimit.x  - rayOrigin.x) / rayDirection.x;
    float t_fary  = (rectLimit.y  - rayOrigin.y) / rayDirection.y;

    if (std::isnan(t_nearx) || std::isnan(t_neary)) return -1;
    if (std::isnan(t_farx)  || std::isnan(t_fary )) return -1;

    // Swap the values properly (if the ray is in the opposite direction)
    if (t_nearx > t_farx) std::swap(t_nearx, t_farx);
    if (t_neary > t_fary) std::swap(t_neary, t_fary);

    // Early rejection
    bool rayIntersects = (t_nearx <= t_fary && t_neary <= t_farx);
    if (!rayIntersects) return -1;

    // Save the "time" for our two collisions
    float time_first_hit = std::max(t_nearx, t_neary);
    return time_first_hit;
}

bool CollisionSystem::checkRayVsWallCollision(
    sf::Vector2f rayOrigin,
    sf::Vector2f rayDirection,
    sf::Vector2f playerSize,
    sf::RectangleShape rect,
    CollisionSystem::CollisionInfo& info
) { 
    // Expand the rect bounds to include the player size
    sf::RectangleShape target;
    target.setPosition(rect.getPosition() - playerSize/2.f);
    target.setSize(rect.getSize() + playerSize);

    sf::Vector2f rectOrigin = target.getPosition();
    sf::Vector2f rectLimit  = target.getPosition() + target.getSize();

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
    bool rayIntersects = (t_nearx <= t_fary && t_neary <= t_farx);
    if (!rayIntersects) return false;

    // Save the "time" for our two collisions
    info.time       = std::max(t_nearx, t_neary); // First collision
    float time_far  = std::min(t_farx, t_fary);   // Second collision

    // t_far < 0 means that the target is opposite to the ray
    if (time_far < 0) return false;
    // if (info.time >= 1.f || info.time < 0) return false;

    // The "t" value is such that:
    // contactPoint = rayOrigin + time*rayDirection;

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
