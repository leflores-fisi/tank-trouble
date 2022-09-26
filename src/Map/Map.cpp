#include <fstream>
#include <iostream>
#include <vector>
#include "Map/Map.hpp"

Map::Map() :
    tilesize(128),
    walls(nullptr) {
}
Map::~Map() {
    delete walls;
}
bool Map::load(std::string filename) {

    // Open map file (currently didn't valid the file format)
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cant open map file");
    }

    // Read an save the pattern of the map (line by line)
    int lineNumber = 0;
    std::string line;
    std::vector<std::string> horizontalWallsPattern;
    std::vector<std::string> verticalWallsPattern;

    while (std::getline(file, line)) {
        std::string wallPattern;
        if (line.empty()) continue;

        // horizontal walls (line 0, 2, 4, ...)
        if (lineNumber % 2 == 0) {
            for (int i = 1; i < line.size(); i+=2) {
                wallPattern += (line[i] == '-' ? "1" : "0");
            }
            horizontalWallsPattern.push_back(wallPattern);
        }
        // vertical walls (line 1, 3, 5, ...)
        else {
            for (int i = 0; i < line.size(); i+=2) {
                wallPattern += (line[i] == '|' ? "1" : "0");
            }
            verticalWallsPattern.push_back(wallPattern);
        }
        lineNumber++;
    }

    // Initialize the walls vector
    if (this->walls != nullptr) delete this->walls;
    this->walls = new std::vector<sf::RectangleShape>();

    int wallWidth = 4;
    // walls templates
    sf::RectangleShape verticalWall(sf::Vector2f(wallWidth, this->tilesize));
    verticalWall.setFillColor(sf::Color(120, 104, 191));
    sf::RectangleShape horizontalWall(sf::Vector2f(this->tilesize, wallWidth));
    horizontalWall.setFillColor(sf::Color(87, 104, 191));

    // Load the walls
    for (int i = 0; i < horizontalWallsPattern.size(); i++) {
        for (int j = 0; j < horizontalWallsPattern[i].size(); j++) {
            if (horizontalWallsPattern[i][j] == '1') {
                sf::Vector2f pos((j+1) * this->tilesize, (i+1) * this->tilesize);
                horizontalWall.setPosition(pos);
                walls->push_back(horizontalWall);
            }
        }
    }
    for (int i = 0; i < verticalWallsPattern.size(); i++) {
        for (int j = 0; j < verticalWallsPattern[i].size(); j++) {
            if (verticalWallsPattern[i][j] == '1') {
                sf::Vector2f pos((j+1) * this->tilesize, (i+1) * this->tilesize);
                verticalWall.setPosition(pos);
                walls->push_back(verticalWall);
            }
        }
    }
    std::cout << "Succesfully loaded map" << std::endl;
    file.close();
    return true;
}
void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& wall : *this->walls) {
        target.draw(wall);
    }
}
std::vector<sf::RectangleShape>* Map::getWalls() {
    return this->walls;
}
