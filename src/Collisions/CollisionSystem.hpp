#pragma once
#include <SFML/Graphics.hpp>
#include "Player/Player.hpp"

namespace tt {

class CollisionSystem {
  public:
    struct CollisionInfo {
        int index;
        float time;
        sf::Vector2f contactNormal = {0, 0};
    };
  private:
    bool checkRayVsRectCollision(
        sf::Vector2f rayOrigin,
        sf::Vector2f rayDirection,
        sf::RectangleShape rect,
        tt::CollisionSystem::CollisionInfo &info
    );
    float getRayVsRectCollisionTime(
        sf::Vector2f rayOrigin,
        sf::Vector2f rayDirection,
        sf::RectangleShape rect
    );
    float getPlayerCollisionTime(
        sf::Vector2f playerCenter,
        sf::Vector2f playerVelocity,
        sf::Vector2f playerSize,
        sf::RectangleShape wall
    );
    bool checkPlayerVsWallCollision(
        sf::Vector2f playerCenter,
        sf::Vector2f playerVelocity,
        sf::Vector2f playerSize,
        sf::RectangleShape wall,
        tt::CollisionSystem::CollisionInfo &info
    );
    void resolvePlayerCollision(
        tt::Player& player,
        tt::CollisionSystem::CollisionInfo info
    );
  public:
    CollisionSystem();
    ~CollisionSystem();
    bool checkPlayerMapCollision(
        tt::Player& player,
        std::vector<sf::RectangleShape>& walls
    );
};
} // namespace tt
