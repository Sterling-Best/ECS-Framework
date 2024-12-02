#include "entity_factory.h"

// Singleton instance accessor
EntityFactory& EntityFactory::getInstance() {
    static EntityFactory instance; // Thread-safe initialization in C++11 and above
    return instance;
}

// Default constructor (private)
EntityFactory::EntityFactory() = default;

// Destructor (private, optional)
EntityFactory::~EntityFactory() = default;

// Creates a new Entity
Entity EntityFactory::CreateEntity() {
    Entity newEntity;
    newEntity.entityId = ECSID::NextEntityId();
    // TODO: Set default bitmask values like isActive
    return newEntity;
}