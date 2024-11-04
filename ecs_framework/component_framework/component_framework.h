#include "component_manager_registry.h"

class ComponentFramework {

public:

	ComponentFramework() 
		: _componentMangerRegistery(ComponentManagerRegistry()) {}

private:

	ComponentManagerRegistry _componentManagerRegistry;
};