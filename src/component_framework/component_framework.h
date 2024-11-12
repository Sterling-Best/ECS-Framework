#include "component_manager_registery.h"

class ComponentFramework {

public:

	ComponentFramework() 
		: _componentManagerRegistery(ComponentManagerRegistery()) {}
 
	
	template<typename ComponentType>
	IComponentManager GetManager() { 
		return _componentManagerRegistery.GetComponentManager<ComponentType>(); 
	}

private:

	ComponentManagerRegistery _componentManagerRegistery;
	//TODO: Add ComponentFactoryRegistery
};