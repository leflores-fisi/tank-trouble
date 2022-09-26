#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Map : public sf::Drawable {
    size_t tilesize;
    std::vector<sf::RectangleShape>* walls;
  public:
    Map();
    ~Map();
    bool load(std::string filename);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    std::vector<sf::RectangleShape>* getWalls();
};
