#include "entity_component_systems_framework.h"


namespace ECSF {

	EntityComponentSystemsFramework _entityComponentSystemFramework;

	void Initialize() {
		_entityComponentSystemFramework = EntityComponentSystemsFramework();
	}

	template<typename ComponentType>
	void AccomponentType() {
		_entityComponentSystemFramework.GetComponentFramework().GetManagerRegistery().GetManagerRepository();
	}

	template<typename ComponentType>
	void ChangeComponent() {
		auto getto = _entityComponentSystemFramework.GetComponentFramework().GetManagerRegistery().GetManagerRepository().GetComponentManager<ComponentType>().GetRepository();
	}

	

}