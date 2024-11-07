#include <unordered_map>
#include <stdexcept>
#include <functional>
#include <vector>
#include <cstdint>
#include "icomponent.h"
#include "is_valid_entity_id_type.h"
#include <any>
#include <sstream> 

template<typename ComponentType, typename EntityIdType>
class ComponentRepository {
	//Static Assert to Ensure that instantiating a ComponentRepository is associated with an ICOmponent ex. ComponentRepostiory<ComponentType>()
	static_assert(std::is_base_of<IComponent, ComponentType>::value, 
		"ComponentType must derive from IComponent");
	// Static Assert to restrict EntityIdType to valid types
	static_assert(IsValidEntityIdType<EntityIdType>::value, 
		"EntityIdType must be a valid type (arithmetic, char, string, or supported type) from IsValidEntityIdType.");

public:

	ComponentRepository() {
	}
	
	//Adds a component of the repository
	void AddComponent(const ComponentType& component) {
		const EntityIdType& entityID = component.entityID;  // Assume ComponentType has GetEntityID() or entityID member
		auto componentIterator = this->_componentPool.find(entityID);
		_CheckNoEntityID(componentIterator);  // Ensure that the entityID doesn't already exist in the pool
		this->_componentPool.emplace(entityID, std::move(component));  // Add the component to the pool
	}

	// Generic method that accepts any container type (e.g., vector, map, etc.)
	template<typename InputIterator>
	void AddComponents(InputIterator begin, InputIterator end) {
		using ValueType = typename std::iterator_traits<InputIterator>::value_type;
		//Handle Interator Lists, Vectors
		if constexpr (std::is_same_v<ValueType, ComponentType>) {
			for (auto it = begin; it != end; ++it) {
				AddComponent(*it);  
			}
		}
		// Handle map-like containers
		else if constexpr (std::is_same_v<ValueType, std::pair<const EntityIdType, ComponentType>>) {
			
			for (auto it = begin; it != end; ++it) {
				AddComponent(it->second);
			}
		}
		else {
			static_assert(_always_false<InputIterator>::value, "Unsupported container type for AddComponents.");
		}
	}

	void RemoveComponent(const EntityIdType& entityID) {
		this->_componentPool.erase(entityID);
	}

	//Generic Method that accepts any container type containing the current EntityIdType
	template<typename InputIterator>
	void RemoveComponents(InputIterator begin, InputIterator end) {
		// Handle both key-value pairs (like in a map) or simple value types
		if constexpr (std::is_same_v<typename std::iterator_traits<InputIterator>::value_type, EntityIdType>) {
			for (auto it = begin; it != end; ++it) {
				RemoveComponent(it->entityID);  // Handle list/vector-like containers (assuming ComponentType has entityID)
			}
		}
		else if constexpr (std::is_same_v<typename std::iterator_traits<InputIterator>::value_type, std::pair<const EntityIdType, ComponentType>>) {
			for (auto it = begin; it != end; ++it) {
				RemoveComponent(it->first);  // Handle map-like containers
			}
		}
		else {
			static_assert(_always_false<InputIterator>::value, "Unsupported container type for RemoveComponents.");
		}
	}

	ComponentType GetComponent(const EntityIdType& entityID) {
		auto componentIterator = this->_componentPool.find(entityID);
		_CheckForEntityID(componentIterator);
		return componentIterator->second;
	}

	void IterateComponentMethod(std::function<void(ComponentType&, const std::vector<std::any>&)> Method, const EntityIdType& entityID, const std::vector<std::any>& args) {
		auto componentIterator = this->_componentPool.find(entityID);
		_CheckForEntityID(componentIterator);
		Method(componentIterator->second, args);
	}
	
	void IterateAllComponentsMethod(std::function<void(ComponentType&, const std::vector<std::any>&)> Method, const std::vector<std::any>& args) {
		// Range-based for loop to iterate over all components in _componentPool
		for (auto& [entityID, component] : _componentPool) {
			// Apply the given method to each component, passing in the args
			Method(component, args);
		}
	}

	template<typename T, typename... Args>
	T IterateComponentFunction(std::function<T(ComponentType&, Args...)> Function, const EntityIdType& entityID, Args... args) {
		auto componentIterator = this->_componentPool.find(entityID);
		_CheckForEntityID(componentIterator);
		return Function(componentIterator->second, args...);
	}

	template<typename ReturnType>
	std::unordered_map<EntityIdType, ReturnType> IterateAllComponentsFunction(
		std::function<ReturnType(ComponentType&, const std::vector<std::any>&)> Function,
		const std::vector<std::any>& args) {
		std::unordered_map<EntityIdType, ReturnType> results;
		// Iterate over all components in _componentPool
		for (auto& [entityID, component] : _componentPool) {
			// Apply the given function to each component, passing in the args
			ReturnType result = Function(component, args);

			// Store the result in the map with entityID as the key
			results.emplace(entityID, result);
		}

		return results;  // Return the map of results
	}

	std::size_t Count() const noexcept {
		return this->_componentPool.size();
	}

	void ReserveSize(std::size_t size) {
		this->_componentPool.rehash(size);
	}

	void Clear() noexcept {
		this->_componentPool.clear();
	}
	
private:

	std::unordered_map<EntityIdType, ComponentType> _componentPool;

	// Helper struct to trigger static_assert for unsupported types
	template<typename T> struct _always_false : std::false_type {};

	void _CheckForEntityID(const auto componentIterator) {
		if (componentIterator == this->_componentPool.end()) {
			std::ostringstream oss;
			oss << componentIterator->first; // Properly use entityID.
			throw std::runtime_error("Component with Entity ID (" + oss.str() + ") not found.");
		}
	}

	void _CheckNoEntityID(const auto componentIterator) {
		if (componentIterator != this->_componentPool.end()) {
			std::ostringstream oss;
			oss << componentIterator->first; // Properly use the entityID.
			throw std::runtime_error("Component with the same entity ID (" + oss.str() + ") already exists.");
		}
	}



};                             