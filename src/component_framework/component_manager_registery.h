//#include "collected_id_configs.h"    // Contains all IdConfig classes
//#include "collected_components.h"    // Contains all Component classes
//#include "collected_factories.h"     // Contains all Factory classes

#include "component_manager_factory.h"
#include "component_manager.h"

class ComponentManagerRegistery {
	
public:

	ComponentManagerRegistery()
		: _componentManagerPool(ankerl::unordered_dense::map<std::type_index, IComponentManager>()),
		_componentManagerFactory(ComponentManagerFactory()) {}

	template<typename ComponentType>
	void CreateComponentManager() {
		ComponentManager<ComponentType> componentManager = ComponentManager<ComponentType>();
		_componentManagerRepository.AddManager(componentManager);
	}

	void AddManager(IComponentManager inputComponentManager) {
		_componentManagerPool.try_emplace(std::type_index(typeid(inputComponentManager)), std::move(inputComponentManager));
	}

	template<typename ComponentType>
	ComponentManager<ComponentType> GetComponentManager() { return _componentManagerPool[std::type_index(ComponentType)]; }

private:
	
	ComponentManagerFactory _componentManagerFactory;
	ankerl::unordered_dense::map<std::type_index, IComponentManager> _componentManagerPool;

};