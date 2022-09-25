#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Map {
    size_t tilesize;
    std::vector<std::string> horizontalWallsPattern;
    std::vector<std::string> verticalWallsPattern;
public:
    Map();
    bool load(std::string filename);
    void draw(sf::RenderWindow& window);
};
