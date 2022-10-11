#pragma once
#include <SFML/Graphics.hpp>
#include "Entity/Entity.hpp"

namespace tt {

#define BULLET_RADIUS 5.f

class Bullet : public tt::Entity {
    sf::Vector2f velocity;
    sf::CircleShape body;
    sf::Vector2f direction;
    sf::Clock lifetime;
    float speed = 300.f;

  public:
    Bullet(sf::Vector2f position, sf::Vector2f direction);
    ~Bullet();
    void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Time getLifeTime();
};
}
