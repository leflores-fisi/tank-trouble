#pragma once
#include <SFML/Graphics.hpp>

#define VEL 150.f

class Player : public sf::Drawable {
    sf::RectangleShape *body;
    sf::Color bodyColor = sf::Color::White;
    sf::RectangleShape *canon;
    sf::Color canonColor = sf::Color::Red;
    sf::VertexArray canonRay;
    sf::Vector2f velocity;
    sf::Vector2f direction; // normalized

  public:
    Player();
    ~Player();
    Player(sf::Vector2f position);

    void update(float dt, std::vector<sf::RectangleShape> &walls);
    void updatePosition();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void addVelocity(float dt, int direction);
    void rotate(float dt, int direction);
    bool checkCollisionForMap(std::vector<sf::RectangleShape>& walls);

    float getAngle();
    void setColor(sf::Color color);
  private:
    bool checkRayVsWallCollition(sf::Vector2f rayOrigin,
                                 sf::Vector2f rayDirection,
                                 sf::RectangleShape rect,
                                 float& t_hit_near,
                                 sf::Vector2f& contact_point,
                                 sf::Vector2f& contact_normal);
};
