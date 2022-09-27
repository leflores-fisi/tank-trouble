#pragma once
#include <SFML/Graphics.hpp>

class Player : public sf::Drawable {
    sf::RectangleShape *body;
    sf::RectangleShape *canon;
    sf::VertexArray canonRay;
    sf::Vector2f direction;
    float velocity;

  public:
    Player();
    ~Player();
    Player(sf::Vector2f position);

    void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void move(float dt, int direction);
    void rotate(float dt, int direction);
    bool checkCollisionForMap(std::vector<sf::RectangleShape>& walls);

    sf::Vector2f getPosition();
    float getAngle();
    sf::Vector2f getVelocity();

    void setPosition(sf::Vector2f position);
    void setAngle(float angle);
    void setColor(sf::Color color);

    sf::Color getColor();
    sf::FloatRect getBounds();
  private:
    bool checkRayVsWallCollition(sf::Vector2f rayOrigin,
                                 sf::Vector2f rayDirection,
                                 sf::RectangleShape rect);
};
