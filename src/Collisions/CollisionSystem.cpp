#include "Collisions/CollisionSystem.hpp"
#include <cmath>
#include <iostream>

tt::CollisionSystem::~CollisionSystem() { }

void tt::CollisionSystem::checkBulletMapCollision(
    tt::Bullet& bullet,
    std::vector<sf::RectangleShape>& walls
) {
    // To perform collision resolution properly, we need check for collisions
    // two times
    // This is because if we check for only one collision, and resolve it
    // changing the bullet's velocity, we might end up in a situation where
    // the new velocity is colliding with another wall
    // This situation happens often in walls corners and edges,
    // so checking again we can resolve that new velocity

    // First collision
    tt::CollisionSystem::CollisionInfo firstCollision;

    bool collision = false;
    for (int i = 0; i < walls.size(); i++) {
        // if (collisionsList.size() == 1) break;
        sf::RectangleShape& currentWall = walls.at(i);
        if (!tt::CollisionSystem::checkRectvsRectCollision(
            bullet.getCenterPosition(),
            bullet.getVelocity(),
            bullet.getSize(),
            currentWall,
            firstCollision
        )) continue;
        if (firstCollision.time >= 0.f && firstCollision.time <= 1.f) {
            collision = true;
            tt::CollisionSystem::resolveBulletCollision(bullet, firstCollision);
            break;
        }
    }
    if (!collision) return;

    // Second collision
    tt::CollisionSystem::CollisionInfo secondCollision;

    for (int i = 0; i < walls.size(); i++) {
        sf::RectangleShape& currentWall = walls.at(i);
        if (!tt::CollisionSystem::checkRectvsRectCollision(
            bullet.getCenterPosition(),
            bullet.getVelocity(),
            bullet.getSize(),
            currentWall,
            firstCollision
        )) continue;
        if (firstCollision.time >= 0.f && firstCollision.time <= 1.f) {
            collision = true;
            tt::CollisionSystem::resolveBulletCollision(bullet, firstCollision);
            break;
        }
    }
}

bool tt::CollisionSystem::checkPlayerMapCollision(
    tt::Player& player,
    std::vector<sf::RectangleShape>& walls
) {

    std::vector<CollisionInfo> collisionsList;

    // Check for collisions with walls
    // Here we just need the time of collision in order to sort them
    for (int i = 0; i < walls.size(); i++) {
        sf::RectangleShape &currentWall = walls[i];

        float hitTime = tt::CollisionSystem::getRectvsRectCollisionTime(
            player.getCenterPosition(),
            player.getVelocity(),
            player.getSize(),
            currentWall
        );
        bool isCollision = (hitTime >= 0 && hitTime <= 1);

        if (isCollision) {
            CollisionInfo collision;
            collision.index = i;
            collision.time = hitTime;
            collisionsList.push_back(collision);
            currentWall.setFillColor(sf::Color::Red);
        }
        else currentWall.setFillColor(sf::Color(87, 104, 191));
    }

    // Sort the collisions by the time proximity
    std::sort(collisionsList.begin(), collisionsList.end(),
        [](const CollisionInfo &a, const CollisionInfo &b) {
            return a.time < b.time;
        }
    );
    // Resolve each collision
    for (CollisionInfo &collisionInfo : collisionsList) {
        sf::RectangleShape &currentWall = walls.at(collisionInfo.index);

        // Collision info must be recalculated
        // because the player velocity changes as we resolve the collisions
        tt::CollisionSystem::checkRectvsRectCollision(
            player.getCenterPosition(),
            player.getVelocity(),
            player.getSize(),
            currentWall,
            collisionInfo // by ref
        );
        tt::CollisionSystem::resolvePlayerCollision(player, collisionInfo);
    }

    bool hasCollided = !collisionsList.empty();
    return hasCollided;
}

float tt::CollisionSystem::getRectvsRectCollisionTime(
    sf::Vector2f rectCenter,
    sf::Vector2f rectVelocity,
    sf::Vector2f rectSize,
    sf::RectangleShape wall
) {

    // Expand the rect bounds
    sf::RectangleShape target;
    target.setPosition(wall.getPosition() - rectSize/2.f);
    target.setSize(wall.getSize() + rectSize);

    return tt::CollisionSystem::getRayVsRectCollisionTime(
        rectCenter,
        rectVelocity,
        target
    );
}

bool tt::CollisionSystem::checkRectvsRectCollision(
    sf::Vector2f rectCenter,
    sf::Vector2f rectVelocity,
    sf::Vector2f rectSize,
    sf::RectangleShape wall,
    CollisionSystem::CollisionInfo& info
) { 
    // Expand the rect bounds to include the player size
    sf::RectangleShape target;
    target.setPosition(wall.getPosition() - rectSize/2.f);
    target.setSize(wall.getSize() + rectSize);

    bool hasCollide = tt::CollisionSystem::checkRayVsRectCollision(
        rectCenter,
        rectVelocity,
        target,
        info
    );
    return hasCollide;
}

/* AABB Logic */
// Note:
// I know this logic is repeated at CollisionSystem::checkRayVsRectCollision()
// but the collition must be recalculated
// this is because as we are resolving collisions, the player's velocity changes
float tt::CollisionSystem::getRayVsRectCollisionTime(
    sf::Vector2f rayOrigin,
    sf::Vector2f rayDirection,
    sf::RectangleShape rect
) { 

    sf::Vector2f rectOrigin = rect.getPosition();
    sf::Vector2f rectLimit  = rect.getPosition() + rect.getSize();

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
    float collision_time = std::max(t_nearx, t_neary); // First collision
    return collision_time;
}

bool tt::CollisionSystem::checkRayVsRectCollision(
    sf::Vector2f rayOrigin,
    sf::Vector2f rayDirection,
    sf::RectangleShape rect,
    CollisionSystem::CollisionInfo& info
) { 

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

void tt::CollisionSystem::resolvePlayerCollision(
    tt::Player& player,
    tt::CollisionSystem::CollisionInfo info
) {
    sf::Vector2f resolvedVelocity = player.getVelocity();

    resolvedVelocity.x += std::abs(resolvedVelocity.x) * info.contactNormal.x * (1.f-info.time);
    resolvedVelocity.y += std::abs(resolvedVelocity.y) * info.contactNormal.y * (1.f-info.time);
    player.setVelocity(resolvedVelocity);
}

void tt::CollisionSystem::resolveBulletCollision(
    tt::Bullet& bullet,
    tt::CollisionSystem::CollisionInfo info
) {
    // Save the bullet's direction
    float dirX = bullet.getDirection().x;
    float dirY = bullet.getDirection().y;

    sf::Vector2f velocityToContact = bullet.getVelocity() * info.time;
    // Calculate the reflected direction and reflected velocity
    sf::Vector2f reflectionVector = bullet.getVelocity() * (1 - info.time);

    if (info.contactNormal.x != 0) {
        dirX = -dirX;
        reflectionVector.x = -reflectionVector.x;
    }
    if (info.contactNormal.y != 0) {
        dirY = -dirY;
        reflectionVector.y = -reflectionVector.y;
    }
    bullet.setVelocity(velocityToContact + reflectionVector);
    bullet.setDirection(sf::Vector2f(dirX, dirY));
}
