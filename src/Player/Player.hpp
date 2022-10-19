#pragma once
#include <SFML/Graphics.hpp>
#include "Entity/Entity.hpp"
#include "Player/Bullet.hpp"

#define PLAYER_VELOCITY 150.f
#define SHOOT_DELAY 0.2f

namespace tt {

class Player : public tt::Entity {
    friend class tt::Bullet;
  public:
    struct Controls {
        sf::Keyboard::Key forward;
        sf::Keyboard::Key rotateLeft;
        sf::Keyboard::Key backward;
        sf::Keyboard::Key rotateRight;
        sf::Keyboard::Key shoot;
    };
  private:
    sf::RectangleShape *body;
    sf::RectangleShape *canon;
    sf::Vector2f velocity;
    sf::Vector2f direction; // normalized
    sf::Clock shootClock;
    bool canShoot = true;
    float size = 30.f;
    sf::Color bodyColor = sf::Color::White;
    sf::Color canonColor = sf::Color::Red;
    Controls controls;

  public:
    Player(std::string id, sf::Vector2f position, tt::Player::Controls controls);
    ~Player();

    void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void rotate(float dt, int direction);
    void handleInput(float dt);

    float getAngle();
    void setColor(sf::Color color);
    void resetColor();
    sf::Vector2f getSize();
    sf::Vector2f getVelocity();
    sf::Vector2f getPosition();
    sf::Vector2f getCenterPosition();
    void setVelocity(sf::Vector2f velocity);
  private:
    void addVelocity(float dt, int direction);
    bool shoot();
};
}
