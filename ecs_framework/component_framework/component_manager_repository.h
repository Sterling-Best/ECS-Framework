#include <unordered_map>
#include <memory>
#include <typeindex>
#include <typeinfo>

#include "component_manager.h"

class ComponentManagerRepository {

public:
	
	ComponentManagerRepository()
		: _componentManagerPool(std::unordered_map<std::type_index, ComponentManager>()) {}

private:

	std::unordered_map<std::type_index, ComponentManager> _componentManagerPool;
};