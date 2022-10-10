#pragma once
#include <SFML/Graphics.hpp>

namespace tt {

class Bullet : public sf::Drawable {
    sf::Vector2f velocity;
    sf::RectangleShape body;
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
