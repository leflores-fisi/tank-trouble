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
    static void instantiate(tt::Entity* entity);
    static void removeEntity(tt::Entity* entity);
    static void removeEntity(std::string id);
    static void deleteEntities();
};
}
