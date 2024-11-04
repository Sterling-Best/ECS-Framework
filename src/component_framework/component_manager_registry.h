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