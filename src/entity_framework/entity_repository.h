/**
 * @class EntityRepository
 * @brief Singleton repository for managing entities in the ECS framework.
 *
 * The EntityRepository provides centralized storage and management of entities.
 * It allows adding, removing, querying, and iterating over entities. The repository
 * ensures entities are uniquely identified by their Entity ID and provides methods
 * for serialization and deserialization for persistence.
 *
 * @details
 * This repository is implemented as a singleton to ensure global access and consistency.
 * It internally uses an `ankerl::unordered_dense::map` to store entitiesin contiguous memory 
 * for fast access and operations . Entities can be added, removed, or queried based on custom
 * predicates or their IDs. The repository also provides utilities for managing the
 * memory usage and load factor of the internal storage.
 *
 * @note This class is thread-unsafe. If multi-threaded access is required,
 *       synchronization mechanisms must be implemented externally.
 *
 * @author Sterling Best
 * @date 2024-12-02
 */

#pragma once
#ifndef ENTITY_REPOSITORY_H
#define ENTITY_REPOSITORY_H

#include <iostream>
#include <sstream>
#include <vector>
#include "ankerl/unordered_dense.h"
#include "../id_framework/ECSID.h"
#include "entity.h"
#include "entity_serializer.h"


// TODO: Make the class thread safe


class EntityRepository {

	using EntityIdType = ECSID::EntityIdType;

public:

	/* Public method to access the singleton instance
		Deleted copy and move constructors/operators */
	static EntityRepository& getInstance();
	EntityRepository(const EntityRepository&) = delete;
	EntityRepository(EntityRepository&&) = delete;
	EntityRepository& operator=(const EntityRepository&) = delete;
	EntityRepository& operator=(EntityRepository&&) = delete;

	Entity* AddEntity(Entity&& entity);

	void AddEntities(std::vector<Entity>&& entities);

	template <typename Predicate>
	auto FindEntities(Predicate predicate) const;

	const Entity* GetEntity(const EntityIdType& entityID) const noexcept;

	const Entity* GetEntityOrThrow(const EntityIdType& entityID);

	template <typename Func, typename... Args>
	void IterateEntityMethod(const EntityIdType& entityID, Func* method, Args&&... args) noexcept;
	
	void RemoveEntity(const EntityIdType& entityID);

	void RemoveEntities(const std::vector<EntityIdType>& entityIDs);

	bool SetEntity(const EntityIdType& entityID, Entity&& newEntity);

	// TODO: Switch serialization to json
	void Load(std::istream& in);
	
	void Save(std::ostream& out) const;

	//Pool Utilities/Configuration

	auto cbegin() const noexcept;

	auto cend() const noexcept;
	
	auto begin() noexcept;
	
	auto end() noexcept;

	void Clear() noexcept;

	const std::size_t Count() const noexcept;

	float LoadFactor() const noexcept;

	double AverageLoadFactor() const noexcept;

	constexpr std::size_t MemoryUsage() const noexcept;

	void ReserveSize(std::size_t size); //TODO: Add Capacity

private:

	EntityRepository();

	~EntityRepository();

	ankerl::unordered_dense::map<EntityIdType, Entity> _entityPool;

};

template <typename Predicate>
auto EntityRepository::FindEntities(Predicate predicate) const {
	return std::views::filter(_entityPool, [predicate](const auto& pair) {
		return predicate(pair.second);
		});
}

template <typename Func, typename... Args>
void EntityRepository::IterateEntityMethod(const EntityIdType& entityID, Func* method, Args&&... args) noexcept {
	auto entityIterator = _entityPool.find(entityID);
	if (entityIterator != _entityPool.end()) {
		(*method)(&(entityIterator->second), std::forward<Args>(args)...);
	}
}

#endif //ENTITY_REPOSITORY_H