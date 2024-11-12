#include <cstdint>
#include <stdexcept>
#include "icomponent.h"
#include "component_repository.h"
#include "icomponent_factory.h"



// ComponentManager.h

#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H


// Base interface for component managers
class IComponentManager {
public:
	virtual ~IComponentManager() = default;
	// Define any common interface methods, if needed, that all ComponentManagers will share.
};

template<typename ComponentType>
class ComponentManager: public IComponentManager {
	static_assert(std::is_base_of<IComponent, ComponentType>::value, "ComponentType must derive from IComponent");

	using EntityIdType = uint64_t;

public:

	ComponentManager() : 
	_componentRepository(ComponentRepository<ComponentType>()) {
		this->_componentFactory = IComponentFactory(); // TODO: Change componentFactory so it finds the appropriate ComponentFactory
	}

	virtual ~ComponentManager() = default;

	void CreateComponent(EntityIdType entityId) {
		// TODO: Need to fix CreateComponent() from ComponentFactory
		ComponentType targetComponent = this->_componentFactory.CreateComponent(entityId);
		this->_componentRepository.AddComponent(targetComponent);
	}

	void AddComponent(ComponentType component) {
		this->_componentRepository.AddComponent(component);
	}

	void RemoveComponent(EntityIdType entityId) {
		this->_componentRepository.RemoveComponent(entityId);
	}

	ComponentType* GetComponent(EntityIdType entityId) {
		return _componentRepository.GetComponent(entityId);
	}

	// TODO: IterateAllCompoentsMethod

	// TODO: Save Compoents

	// TODO: Load Compoents

	//ComponentRepository<ComponentType> GetRepository() { return _componentRepository; }

private:

	ComponentRepository<ComponentType> _componentRepository;
	IComponentFactory _componentFactory;

};

#endif // COMPONENT_MANAGER_H