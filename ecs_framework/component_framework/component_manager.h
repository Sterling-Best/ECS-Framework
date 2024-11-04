#include <cstdint>
#include <stdexcept>
#include "icomponent.h"
#include "component_repository.h"



template<typename ComponentType, typename EntityIdType>
class ComponentManager {
	static_assert(std::is_base_of<IComponent, ComponentType>::value, "ComponentType must derive from IComponent");

public:

	void ComponentRepository() {
		
	}

	void CreateComponentRepository() {
		this->_componentRepository = ComponentRepository<ComponentType, EntityIdType>();
	}

	void CreateComponent() {
		this->_componentRepository->AddComponent()
	}

	void AddComponent() {
		this->_componentRepostory.AddComponent();
	}

private:

	ComponentRepository<ComponentType, EntityIdType> _componentRepository;

};