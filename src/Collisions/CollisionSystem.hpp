#pragma once
#include <SFML/Graphics.hpp>
#include "../Player.hpp"

class CollisionSystem {
     struct Collision {
          int index;
          float t_hit_near;
     };
     bool checkRayVsWallCollition(sf::Vector2f rayOrigin,
                                 sf::Vector2f rayDirection,
                                 sf::RectangleShape rect,
                                 float& t_hit_near,
                                 sf::Vector2f& contact_point,
                                 sf::Vector2f& contact_normal);
  public:
     CollisionSystem();
     ~CollisionSystem();
     bool checkPlayerMapCollition(
          Player& player,
          std::vector<sf::RectangleShape>& walls
     );
};
