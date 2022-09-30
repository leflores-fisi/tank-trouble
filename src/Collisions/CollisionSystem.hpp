#pragma once
#include <SFML/Graphics.hpp>
#include "../Player.hpp"

class CollisionSystem {
  public:
     struct CollisionInfo {
          int index;
          float t_hit;
          sf::Vector2f contactNormal;
     };
  private:
     bool checkRayVsWallCollision(sf::Vector2f rayOrigin,
                                 sf::Vector2f rayDirection,
                                 sf::RectangleShape rect,
                                 CollisionSystem::CollisionInfo &info);
     void resolvePlayerCollision(Player& player, CollisionSystem::CollisionInfo info);
  public:
     CollisionSystem();
     ~CollisionSystem();
     bool checkPlayerMapCollision(
          Player& player,
          std::vector<sf::RectangleShape>& walls
     );
};
