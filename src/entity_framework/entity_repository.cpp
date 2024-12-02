#include "entity_repository.h"

// Public method to access the singleton instance
EntityRepository& EntityRepository::getInstance() {
	static EntityRepository instance; // Thread-safe initialization in C++11 and above
	return instance;
}

EntityRepository::EntityRepository() = default;

EntityRepository::~EntityRepository() {
	this->Clear();
}

Entity* EntityRepository::AddEntity(Entity&& entity) {
	const EntityIdType entityID = entity.entityId;
	auto [iterator, inserted] = _entityPool.try_emplace(entityID, std::move(entity));
	return inserted ? &iterator->second : nullptr;
}

void EntityRepository::AddEntities(std::vector<Entity>&& entities) {
	for (auto& entity : entities) {
		AddEntity(std::move(entity));
	}
}

const Entity* EntityRepository::GetEntity(const EntityIdType& entityID) const noexcept {
	auto componentIterator = _entityPool.find(entityID);
	return componentIterator != _entityPool.end() ? &componentIterator->second : nullptr;
}

const Entity* EntityRepository::GetEntityOrThrow(const EntityIdType& entityID) {
	auto entityIterator = _entityPool.find(entityID);
	if (entityIterator == _entityPool.end()) {
		// Create an error message with the missing entity ID
		std::ostringstream errorMsg;
		errorMsg << "Entity with Entity ID [ " << entityID << " ] not found.";
		throw std::out_of_range(errorMsg.str());
	}
	return &entityIterator->second;
}

void EntityRepository::RemoveEntity(const EntityIdType& entityID) {
	this->_entityPool.erase(entityID);
}

void EntityRepository::RemoveEntities(const std::vector<EntityIdType>& entityIDs) {
	for (const auto& entityID : entityIDs) {
		RemoveEntity(entityID);
	}
}

bool EntityRepository::SetEntity(const EntityIdType& entityID, Entity&& newEntity) {
	auto it = _entityPool.find(entityID);
	if (it != _entityPool.end()) {
		it->second = std::move(newEntity);
		return true;
	}
	return false;
}

// Save/Load

void EntityRepository::Load(std::istream& in) {
	Entity entity;
	EntityIdType entityID;
	while (in >> entityID >> entity) {
		AddEntity(std::move(entity));
	}
}

void EntityRepository::Save(std::ostream& out) const {
	for (const auto& [entityID, entity] : _entityPool) {
		out << entityID << " " << EntitySerializer.Serialize(entity) << "\n";
	}
}

//Pool Utilities/Configuration

auto EntityRepository::cbegin() const noexcept { return _entityPool.cbegin(); }

auto EntityRepository::cend() const noexcept { return _entityPool.cend(); }

auto EntityRepository::begin() noexcept { return _entityPool.begin(); }

auto EntityRepository::end() noexcept { return _entityPool.end(); }

void EntityRepository::Clear() noexcept {
	this->_entityPool.clear();
}

const std::size_t EntityRepository::Count() const noexcept {
	return this->_entityPool.size();
}

float EntityRepository::LoadFactor() const noexcept {
	return _entityPool.load_factor();
}

double EntityRepository::AverageLoadFactor() const noexcept {
	return _entityPool.load_factor() / _entityPool.max_load_factor();
}

constexpr std::size_t EntityRepository::MemoryUsage() const noexcept {
	return _entityPool.size() * sizeof(std::pair<EntityIdType, Entity>);
}

// TODO: Add Capacity
void EntityRepository::ReserveSize(std::size_t size) {
	_entityPool.rehash(size);
}

