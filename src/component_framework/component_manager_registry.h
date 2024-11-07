#include "collected_id_configs.h"    // Contains all IdConfig classes
#include "collected_components.h"    // Contains all Component classes
#include "collected_factories.h"     // Contains all Factory classes

#include "component_manager_repository.h"
#include "component_manager_factory.h"

class ComponentManagerRegistry {

public:

	ComponentManagerRegistry()
		: _componentManagerRepository(ComponentManagerRepository()),
		_componentManagerFactory(ComponentManagerFactory()) {}

private:
	
	ComponentManagerRepository _componentManagerRepository;
	ComponentManagerFactory _componentManagerFactory;

};