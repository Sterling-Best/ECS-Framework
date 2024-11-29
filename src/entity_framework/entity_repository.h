#include "ankerl/unordered_dense.h"
#include "entity.h"

#include <ECSID.h>


class EntityRepository {

	using EntityIdType = ECSID::GetEntityIdType(); // Default uint64_t

public:

	EntityRepository() {

	}

	~EntityRepository() {
		this->Clear();
	}

	Entity* AddEntity(Entity&& entity) {
		const EntityIdType entityID = entity.entityID;
		auto [iterator, inserted] = _entityPool.try_emplace(entityID, std::move(entity));
		return inserted ? &iterator->second : nullptr;
	}

	void AddEntities(std::vector<Entity>&& entities) {
		for (auto& entity : entities) {
			AddEntity(std::move(entity));
		}
	}
	
	void RemoveEntity(const EntityIdType& entityID) {
		this->_entityPool.erase(entityID);
	}

	void RemoveEntities(const std::vector<EntityIdType>& entityIDs) {
		for (const auto& entityID : entityIDs) {
			RemoveEntity(entityID);
		}
	}

	template <typename Predicate>
	auto FindEntities(Predicate predicate) const {
		return std::views::filter(_entityPool, [predicate](const auto& pair) {
			return predicate(pair.second);
			});
	}
	
	const Entity* GetEntity(const EntityIdType& entityID) const noexcept {
		auto componentIterator = _entityPool.find(entityID);
		return componentIterator != _entityPool.end() ? &componentIterator->second : nullptr;
	}

	const ComponentType* GetEntityOrThrow(const EntityIdType& entityID) {
		auto entityIterator = _entityPool.find(entityID);
		if (entityIterator == _entityPool.end()) {
			// Create an error message with the missing entity ID
			std::ostringstream errorMsg;
			errorMsg << "Entity with Entity ID [ " << entityID << " ] not found.";
			throw std::out_of_range(errorMsg.str());
		}
		return &entityIterator->second;
	}

	bool SetEntity(const EntityIdType& entityID, Entity&& newEntity) {
		auto it = _entityPool.find(entityID);
		if (it != _entityPool.end()) {
			it->second = std::move(newEntity);
			return true;
		}
		return false;
	}

	template <typename Func, typename... Args>
	void IterateEntityMethod(const EntityIdType& entityID, Func* method, Args&&... args) noexcept {
		auto entityIterator = _entityPool.find(entityID);
		if (entityIterator != _entityPool.end()) {
			(*method)(&(entityIterator->second), std::forward<Args>(args)...);
		}
	}

	//Pool Utilities/Configuration

	void ReserveSize(std::size_t size) {
		if (size > _entityPool.capacity()) {
			_entityPool.rehash(size);
		}
	}
	
	void Clear() noexcept {
		this->_entityPool.clear();
	}

	// TODO: Switch serialization to json
	
	void Save(std::ostream& out) const {
		for (const auto& [entityID, entity] : _entityPool) {
			out << entityID << " " << entity.Serialize() << "\n";
		}
	}

	void Load(std::istream& in) {
		Entity entity;
		EntityIdType entityID;
		while (in >> entityID >> entity) {
			AddEntity(std::move(entity));
		}
	}

	//Pool Info/Diagnosis

	auto cbegin() const noexcept { return _entityPool.cbegin(); }
	auto cend() const noexcept { return _entityPool.cend(); }
	auto begin() noexcept { return _entityPool.begin(); }
	auto end() noexcept { return _entityPool.end(); }

	const std::size_t Count() const noexcept {
		return this->_entityPool.size();
	}

	std::size_t Capacity() const noexcept {
		return _entityPool.capacity();
	}

	float LoadFactor() const noexcept {
		return _entityPool.load_factor();
	}

	double AverageLoadFactor() const noexcept {
		return _entityPool.load_factor() / _entityPool.max_load_factor();
	}

	constexpr std::size_t MemoryUsage() const noexcept {
		return _entityPool.size() * sizeof(std::pair<EntityIdType, Entity>);
	}

private:

	ankerl::unordered_dense::map<EntityIdType, Entity> _entityPool;

};