#pragma once
#include <SFML/Graphics.hpp>
#include "Player/Player.hpp"
#include "Player/Bullet.hpp"

namespace tt {

class CollisionSystem {
  public:
    struct CollisionInfo {
        int index;
        float time;
        sf::Vector2f contactNormal = {0, 0};
    };
  private:
    static bool checkRayVsRectCollision(
        sf::Vector2f rayOrigin,
        sf::Vector2f rayDirection,
        sf::RectangleShape rect,
        tt::CollisionSystem::CollisionInfo &info
    );
    static float getRayVsRectCollisionTime(
        sf::Vector2f rayOrigin,
        sf::Vector2f rayDirection,
        sf::RectangleShape rect
    );
    static float getRectvsRectCollisionTime(
        sf::Vector2f playerCenter,
        sf::Vector2f playerVelocity,
        sf::Vector2f playerSize,
        sf::RectangleShape wall
    );
    static bool checkRectvsRectCollision(
        sf::Vector2f playerCenter,
        sf::Vector2f playerVelocity,
        sf::Vector2f playerSize,
        sf::RectangleShape wall,
        tt::CollisionSystem::CollisionInfo &info
    );
    static void resolvePlayerCollision(
        tt::Player& player,
        tt::CollisionSystem::CollisionInfo info
    );
    static void resolveBulletCollision(
        tt::Bullet& bullet,
        tt::CollisionSystem::CollisionInfo info
    );
  public:
    // Explicitly disallow copying
    CollisionSystem(const CollisionSystem&) = delete;
    CollisionSystem& operator=(const CollisionSystem&) = delete;

    static bool checkPlayerMapCollision(
        tt::Player& player,
        std::vector<sf::RectangleShape>& walls
    );
    static void checkBulletMapCollision(
        tt::Bullet& bullet,
        std::vector<sf::RectangleShape>& walls
    );
  private:
    ~CollisionSystem();
};
} // namespace tt
