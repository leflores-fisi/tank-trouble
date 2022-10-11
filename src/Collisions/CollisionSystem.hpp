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
        CollisionInfo &info
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
        CollisionSystem::CollisionInfo &info
    );
    void resolvePlayerCollision(
        Player& player,
        CollisionSystem::CollisionInfo info
    );
  public:
    CollisionSystem();
    ~CollisionSystem();
    bool checkPlayerMapCollision(
        Player& player,
        std::vector<sf::RectangleShape>& walls
    );
};
} // namespace tt
