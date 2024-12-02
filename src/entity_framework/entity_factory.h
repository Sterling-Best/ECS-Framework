/**
 * @file EntityFactory.h
 * @brief Declares the EntityFactory class for creating ECS entities.
 *
 * This file contains the declaration of the EntityFactory singleton,
 * which is responsible for creating entities and initializing their values in the ECS framework.
 *
 * @author Your Name
 * @date 2024-12-02
 */

#pragma once
#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "../id_framework/ECSID.h"
#include "Entity.h"

 /**
  * @class EntityFactory
  * @brief Specialized Singleton constructor class for entities.
  */
class EntityFactory {
	using EntityIdType = ECSID::EntityIdType;

public:
	/**
	 * @brief Accesses the singleton instance of EntityFactory.
	 * @return EntityFactory& Reference to the singleton instance.
	 */
	static EntityFactory& getInstance();

	// Deleted copy and move constructors/operators
	EntityFactory(const EntityFactory&) = delete;
	EntityFactory(EntityFactory&&) = delete;
	EntityFactory& operator=(const EntityFactory&) = delete;
	EntityFactory& operator=(EntityFactory&&) = delete;

	/**
	 * @brief Creates a new Entity.
	 * @return Entity The newly created entity with a unique ID.
	 */
	Entity CreateEntity();

private:
	// Private constructor to prevent instantiation
	EntityFactory();

	// Private destructor to prevent external destruction (optional)
	~EntityFactory();
};

#endif // ENTITYFACTORY_H