#pragma once
#include <SFML/Graphics.hpp>
#include "Player/Bullet.hpp"

#define VEL 150.f

class Player : public sf::Drawable {
    sf::RectangleShape *body;
    sf::Color bodyColor = sf::Color::White;
    sf::RectangleShape *canon;
    sf::Color canonColor = sf::Color::Red;
    sf::VertexArray canonRay;
    sf::Vector2f velocity;
    sf::Vector2f direction; // normalized
    std::vector<Bullet> bullets;

  public:
    Player();
    ~Player();
    Player(sf::Vector2f position);

    void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void rotate(float dt, int direction);
    bool shoot();
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
};
