#include "component_framework/component_framework.h"
#include "entity_framework/entity_framework.h"
#include "id_framework/ECSID.h"

class EntityComponentSystemsFramework {

	using EntityIdType = decltype(ECSID::GetEntityIdType());

	// TODO: Make EntityComponentSystemsFramework into a Singleton
	//Want to use Mid-level encapsulation accross the framework frameworkclass.managerclass<type>().component

public:

	EntityComponentSystemsFramework() {
		_componentFramework = ComponentFramework();
		// TODO: Initialize Entity Framework
	}

	template<typename ComponentType>
	void AddComponent(EntityIdType entityId) {
		_componentFramework.GetManager<ComponentType>().AddComponent(entityId);
	}

	// TODO: IterateAllComponentsMethod - Iterate over all components of a specific type with a  method
	template<typename ComponentType>
	void ItterateAllComponentsMethod() {
		_componentFramework.GetManager<ComponentType>().ItterateAllCompoentsMethod();
	}

	// TODO: CreateEntity

	// TODO: Remove Entity

	// TODO: RemoveComponents - Remove component based on specific type

	// TODO: GetComponent - 

	// TODO: SetComponent - Sets or Replaces the Component with the aurguement (make sure to reflect it in the associated entity)
	
	// TOOO: IterateAllComponentsFunction - Iterate over all compoents of a specitic type with a function
	
private:

	ComponentFramework _componentFramework;

};