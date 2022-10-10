#include "Entity/Entity.hpp"
#include "Entity/EntityManager.hpp"

tt::Entity::Entity() {
    this->id = "entity";
    tt::EntityManager::instantiate(this);
}
tt::Entity::~Entity() { }
