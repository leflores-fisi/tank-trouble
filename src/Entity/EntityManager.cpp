#include "Entity/EntityManager.hpp"

void tt::EntityManager::instantiate(tt::Entity* entity) {
    tt::EntityManager::entities.push_back(entity);
}
void tt::EntityManager::removeEntity(tt::Entity* entity) {
    for (int i = 0; i < tt::EntityManager::entities.size(); i++) {
        if (tt::EntityManager::entities.at(i) == entity) {
            tt::EntityManager::entities.erase(tt::EntityManager::entities.begin() + i);
            return;
        }
    }
}
void tt::EntityManager::removeEntity(std::string id) {
    for (int i = 0; i < tt::EntityManager::entities.size(); i++) {
        if (tt::EntityManager::entities.at(i)->id == id) {
            tt::EntityManager::entities.erase(tt::EntityManager::entities.begin() + i);
            return;
        }
    }
}
void tt::EntityManager::deleteEntities() {
    for (const auto e : tt::EntityManager::entities) {
        delete e;
    }
    tt::EntityManager::entities.clear();
}
