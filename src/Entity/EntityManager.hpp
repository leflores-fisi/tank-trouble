#pragma once
#include "Entity/Entity.hpp"

namespace tt {

// Entity manager singleton
class EntityManager {
  public:
    inline static std::vector<tt::Entity*> entities = std::vector<tt::Entity*>();
    // Explicitly disallow copying
    EntityManager(const EntityManager&) = delete;
    EntityManager& operator=(const EntityManager&) = delete;
    ~EntityManager();

    static std::vector<tt::Entity*> querySelectorAll(std::string query);
    static tt::Entity* getById(std::string id);
    static void instantiate(tt::Entity* entity);
    static void deleteEntity(tt::Entity* entity);
    static void deleteEntity(std::string id);
    static void deleteALlEntities();
    static int  entityCount();
};
}
