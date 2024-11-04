#include "entity_component_systems_framework.h"

namespace ECSF {

	void Initialize() {
		_entityComponentSystemFramekwork = EntityComponentSystemsFramework();
	}

	namespace {
		EntityComponentSystemsFramework _entityComponentSystemFramekwork;

	}

}