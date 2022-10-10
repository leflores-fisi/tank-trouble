#include <iostream>
#include "Entity/EntityManager.hpp"

tt::Entity* tt::EntityManager::getById(std::string query_id) {
    if (query_id.empty()) throw std::invalid_argument("Query cannot be empty");

    for (tt::Entity* e : tt::EntityManager::entities) {
        if (e->id == query_id) return e;
    }
    return nullptr;
}

/**
 * @brief Return a vector of tt::Entity* based on a given query
 * @param query A string containing the query, e.g. ".player" or "#player1".
 * 
 * @throws std::invalid_argument if the query is invalid
 * @note The query is case sensitive, css-like queries
 * 
 * @return A vector of tt::Entity* that match the query
 * or a vector of Entity* if the query is a class.
 */
std::vector<tt::Entity*> tt::EntityManager::querySelectorAll(std::string query) {
    if (query.empty()) throw std::invalid_argument("Query cannot be empty");

    char selector = query.at(0);
    std::vector<tt::Entity*> entities;

    switch (selector) {
        case '#': {
            std::string idQuery = query.substr(1, query.size() - 1);
            tt::Entity* e = tt::EntityManager::getById(idQuery);
            if (e) entities.push_back(e);

            return entities;
        }
        case '.': {
            std::string classQuery = query.substr(1, query.size() - 1);
            for (tt::Entity* e : tt::EntityManager::entities) {
                if (e->classList.contains(classQuery)) {
                    entities.push_back(e); 
                }
            }
            return entities;
        }
        default: {
            throw std::invalid_argument("Query: '" + query + "' is invalid");
        }
    }
}

void tt::EntityManager::instantiate(tt::Entity* entity) {
    tt::EntityManager::entities.push_back(entity);
}
void tt::EntityManager::deleteEntity(tt::Entity* entityToRemove) {
    for (int i = 0; i < tt::EntityManager::entities.size(); i++) {
        auto currentEntity = tt::EntityManager::entities.at(i);
        if (currentEntity == entityToRemove) {
            tt::EntityManager::entities.erase(tt::EntityManager::entities.begin() + i);
            delete currentEntity;
            return;
        }
    }
}
void tt::EntityManager::deleteEntity(std::string idToRemove) {
    for (int i = 0; i < tt::EntityManager::entities.size(); i++) {
        auto currentEntity = tt::EntityManager::entities.at(i);
        if (currentEntity->id == idToRemove) {
            tt::EntityManager::entities.erase(tt::EntityManager::entities.begin() + i);
            delete currentEntity;
            return;
        }
    }
}
void tt::EntityManager::deleteALlEntities() {
    if (tt::EntityManager::entities.empty()) return;

    for (const auto e : tt::EntityManager::entities) {
        std::cout << "Deleting entity: " << e->id << std::endl;
        delete e;
    }
    tt::EntityManager::entities.clear();
}
