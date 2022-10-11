#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>

namespace tt {

#define DESTROY_CLASS "destroy"
#define HIDDEN_CLASS "hidden"

// Base class for entities
class Entity : public sf::Drawable {
  public:
    struct ClassList {
        std::vector<std::string> classnames;
        void add     (std::string classname);
        bool contains(std::string classname);
    };

    std::string id;
    ClassList classList;
    Entity(std::string id);
    virtual ~Entity();
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};
}
