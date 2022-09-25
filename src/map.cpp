#include <fstream>
#include <iostream>
#include <vector>
#include "map.hpp"

Map::Map() :
    tilesize(128),
    horizontalWallsPattern(std::vector<std::string>()),
    verticalWallsPattern(std::vector<std::string>()) {
}

bool Map::load(std::string filename) {
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cant open map file");
    }
    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        std::string wallPattern;
        if (line.empty()) continue;

        // horizontal walls
        if (lineNumber % 2 == 0) {
            for (int i = 0; i < line.size(); i++) {
                if (i % 2 != 0) wallPattern += (line[i] == '-' ? "1" : "0");
            }
            this->horizontalWallsPattern.push_back(wallPattern);
        }
        // vertical walls
        else {
            for (int i = 0; i < line.size(); i++) {
                if (i % 2 == 0) wallPattern += (line[i] == '|' ? "1" : "0");
            }
            this->verticalWallsPattern.push_back(wallPattern);
        }
        lineNumber++;
    }

    file.close();

    return true;
}
void Map::draw(sf::RenderWindow& window) {

    int wallWidth = 4;

    sf::RectangleShape verticalWall(sf::Vector2f(wallWidth, this->tilesize));
    verticalWall.setFillColor(sf::Color(120, 104, 191));
    sf::RectangleShape horizontalWall(sf::Vector2f(this->tilesize, wallWidth));
    horizontalWall.setFillColor(sf::Color(87, 104, 191));

    for (int i = 0; i < horizontalWallsPattern.size(); i++) {
        for (int j = 0; j < horizontalWallsPattern[i].size(); j++) {
            if (horizontalWallsPattern[i][j] == '1') {
                horizontalWall.setPosition(sf::Vector2f((j+1) * this->tilesize, (i+1) * this->tilesize));
                window.draw(horizontalWall);
            }
        }
    }
    for (int i = 0; i < verticalWallsPattern.size(); i++) {
        for (int j = 0; j < verticalWallsPattern[i].size(); j++) {
            if (verticalWallsPattern[i][j] == '1') {
                verticalWall.setPosition(sf::Vector2f((j+1) * this->tilesize, (i+1) * this->tilesize));
                window.draw(verticalWall);
            }
        }
    }
}
