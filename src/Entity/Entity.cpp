#include <SFML/Graphics.hpp>
#include "Entity/Entity.hpp"
#include "Entity/EntityManager.hpp"

void tt::Entity::ClassList::add(std::string classname) {
    this->classnames.push_back(classname);
}
bool tt::Entity::ClassList::contains(std::string classname) {
    return std::find(
        classnames.begin(), classnames.end(), classname
    ) != classnames.end();
}

tt::Entity::Entity(std::string id) :
    id(id) {

    if (this->id.empty()) {
        this->id = "entity-" + std::to_string(tt::EntityManager::entityCount());
    }
}
tt::Entity::~Entity() { }
