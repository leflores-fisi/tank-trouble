#pragma once
#include <SFML/Graphics.hpp>
#include "Entity/Entity.hpp"

namespace tt {

#define BULLET_RADIUS 5.f
#define BULLET_HIT_DELAY 0.1f

class Bullet : public tt::Entity {
    sf::Vector2f velocity;
    sf::Vector2f direction;
    sf::Clock lifetime;
    float speed = 300.f;

  public:
    sf::CircleShape body;
    Bullet(sf::Vector2f position, sf::Vector2f direction);
    ~Bullet();
    void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Time getLifeTime();
    sf::Vector2f getSize();
    sf::Vector2f getVelocity();
    void setVelocity(sf::Vector2f vel);
    void calculateVelocity(float dt);

    sf::Vector2f getDirection();
    void setDirection(sf::Vector2f velocity);

    sf::Vector2f getCenterPosition();
    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f pos);
};
}
