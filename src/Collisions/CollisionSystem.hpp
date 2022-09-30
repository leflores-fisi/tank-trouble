#pragma once
#include <SFML/Graphics.hpp>
#include "../Player.hpp"

class CollisionSystem {
  public:
    struct CollisionLog {
      int index;
      float time;
    };
    struct CollisionInfo {
        int index;
        float time;
        sf::Vector2f contactNormal;
    };
  private:
    bool checkRayVsWallCollision(
        sf::Vector2f rayOrigin,
        sf::Vector2f rayDirection,
        sf::Vector2f playerSize,
        sf::RectangleShape rect,
        CollisionSystem::CollisionInfo &info
    );
    void resolvePlayerCollision(
        Player& player,
        CollisionSystem::CollisionInfo info
    );
    float getRayCollisionTime(
        sf::Vector2f rayOrigin,
        sf::Vector2f rayDirection,
        sf::Vector2f playerSize,
        sf::RectangleShape rect
    );
  public:
    CollisionSystem();
    ~CollisionSystem();
    bool checkPlayerMapCollision(
        Player& player,
        std::vector<sf::RectangleShape>& walls
    );
};
