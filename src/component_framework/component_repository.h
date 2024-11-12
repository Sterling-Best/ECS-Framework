#pragma once

#include "ankerl/unordered_dense.h"

#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <functional>
#include <vector>
#include <cstdint>
#include <any>
#include <sstream> 
#include <memory_resource>
#include <optional>
#include <string>
#include <tuple>
#include <type_traits>

//#include "../id_framework/is_valid_entity_id_type.h"  // Adjust the path if id_framework is in a sibling directory.
#include "icomponent.h"
#include "../utilities/custom_hash.h"

#ifdef _MSC_VER
#define FORCE_INLINE __forceinline
#else
#define FORCE_INLINE inline __attribute__((always_inline))
#endif

template<typename ComponentType>
class ComponentRepository {

	using EntityIdType = uint64_t;

	//Static Assert to Ensure that instantiating a ComponentRepository is associated with an ICOmponent ex. ComponentRepostiory<ComponentType>()
	static_assert(std::is_base_of<IComponent, ComponentType>::value, 
		"ComponentType must derive from IComponent");

	using EntityIdHash = CustomHash<EntityIdType>;


public:



	/*ankerl::unordered_dense::map<EntityIdType, ComponentType, ankerl::unordered_dense::hash<EntityIdType>> _componentPool;*/
	
	/*std::unordered_map<EntityIdType, ComponentType> _componentPool;*/

	ComponentRepository(std::pmr::memory_resource* resource = std::pmr::get_default_resource())
		: _buffer(resource)
		//_componentPool(0, EntityIdHash(), std::equal_to<EntityIdType>()) 
		{
		_componentPool.max_load_factor(0.5f);
	}
	
	// Default constructor
	/*ComponentRepository() {
		_componentPool.max_load_factor(0.9f);
	}*/
	
	//////Adds a component of the repository
	inline ComponentType* AddComponent(ComponentType component) {
		const EntityIdType entityID = component.entityID;
		auto [iterator, inserted] = _componentPool.try_emplace(entityID, std::move(component));
		return inserted ? &iterator->second : nullptr;
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

	// Use the macro in your function
	FORCE_INLINE ComponentType* GetComponent(const EntityIdType& entityID) noexcept {
		auto componentIterator = _componentPool.find(entityID);
		return componentIterator != _componentPool.end() ? &componentIterator->second : nullptr;
	}

	FORCE_INLINE ComponentType* GetComponentOrThrow(const EntityIdType& entityID) {
		auto componentIterator = _componentPool.find(entityID);
		if (componentIterator == _componentPool.end()) {
			// Create an error message with the missing entity ID
			std::ostringstream errorMsg;
			errorMsg << "Component with Entity ID " << entityID << " not found.";
			throw std::out_of_range(errorMsg.str());
		}
		return &componentIterator->second;
	}

	template <typename Func, typename... Args>
	FORCE_INLINE void IterateComponentMethod(Func* method, const EntityIdType& entityID, Args&&... args) noexcept {
		auto componentIterator = _componentPool.find(entityID);

		//// Use assert in debug mode to catch missing entityID cases during development
		//assert((componentIterator != _componentPool.end()) && "Entity ID not found");

		//// Early return in production if entityID is not found, avoiding exception overhead
		//if (componentIterator == _componentPool.end()) {
		//    return;
		//}

		// Call the method using std::invoke and passing the address of the component (assuming it expects a pointer)
		(*method)(&(componentIterator->second), args ...);
	}

	template <typename Func, typename... Args>
	void IterateAllComponentsMethod(Func* method, Args&&... args) {
		// Range-based for loop to iterate over all components in _componentPool
		for (auto& [entityID, component] : _componentPool) {
			// Call the method pointer with the component and forward additional args
			(*method)(&component, args ...);
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
	

	//using EntityIdHash = std::conditional_t<
	//	std::is_arithmetic<EntityIdType>::value ||
	//	std::is_same_v<EntityIdType, std::string> ||
	//	std::is_same_v<EntityIdType, std::wstring> ||
	//	std::is_enum<EntityIdType>::value,
	//	ankerl::unordered_dense::hash<EntityIdType>,
	//	std::hash<EntityIdType>>;

	//using EntityAllocator = std::conditional_t<
	//	std::is_arithmetic<EntityIdType>::value ||
	//	std::is_same_v<EntityIdType, std::string> ||
	//	std::is_same_v<EntityIdType, std::wstring>,
	//	std::pmr::polymorphic_allocator<std::pair<EntityIdType, ComponentType>>,
	//	std::allocator<std::pair<EntityIdType, ComponentType>>>;

	std::pmr::monotonic_buffer_resource _buffer;
	ankerl::unordered_dense::map<EntityIdType, ComponentType, EntityIdHash, std::equal_to<EntityIdType>> _componentPool;
	//ankerl::unordered_dense::map<EntityIdType, ComponentType, EntityIdHash, std::equal_to<EntityIdType>> _componentPool;

	// Helper struct to trigger static_assert for unsupported types
	template<typename T> struct _always_false : std::false_type {};
	void _CheckForEntityID(const auto& componentIterator) {
		if (componentIterator == this->_componentPool.end()) {
			throw std::runtime_error("Component with specified Entity ID not found.");
		}
	}

	void _CheckNoEntityID(const auto componentIterator) {
		if (componentIterator != this->_componentPool.end()) {
			throw std::runtime_error("Component with the same entity ID already exists.");
		}
	}

};