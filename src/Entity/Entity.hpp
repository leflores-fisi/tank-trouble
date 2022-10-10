#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>

namespace tt {
// Base class for entities
class Entity : public sf::Drawable {
  public:
    std::string id;
    struct ClassList {
        std::vector<std::string> classnames;
        void add(std::string classname) {
            this->classnames.push_back(classname);
        }
        bool contains(std::string classname) {
            return std::find(
                classnames.begin(), classnames.end(), classname
            ) != classnames.end();
        }

    };
    ClassList classList;
    Entity(std::string id);
    virtual ~Entity();
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};
}
