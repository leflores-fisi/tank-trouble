#include <SFML/Graphics.hpp>
#include "Entity/Entity.hpp"
#include "Entity/EntityManager.hpp"

tt::Entity::Entity(std::string id) :
    id(id) {

    if (this->id.empty()) {
        this->id = "entity-" + std::to_string(tt::EntityManager::entityCount());
    }
}
tt::Entity::~Entity() { }
