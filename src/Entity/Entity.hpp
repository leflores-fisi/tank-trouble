#pragma once
#include <SFML/Graphics.hpp>

namespace tt {

// Base class for entities
class Entity : public sf::Drawable {
  public:
    std::string id;
    struct classList {
        
    } classList;
    Entity();
    virtual ~Entity();
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};
}
