#pragma once
#include <SFML/Graphics.hpp>

class Player : public sf::Drawable {
    sf::RectangleShape *body;
    sf::Color bodyColor = sf::Color::White;
    sf::RectangleShape *canon;
    sf::Color canonColor = sf::Color::Red;
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

    float getAngle();
    void setColor(sf::Color color);
  private:
    bool checkRayVsWallCollition(sf::Vector2f rayOrigin,
                                 sf::Vector2f rayDirection,
                                 sf::RectangleShape rect);
};
