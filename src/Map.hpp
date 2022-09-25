#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Map : public sf::Drawable {
    size_t tilesize;
    std::vector<std::string> horizontalWallsPattern;
    std::vector<std::string> verticalWallsPattern;
public:
    Map();
    bool load(std::string filename);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
