#include <typeindex>

#include "ecs_id_registery.h"
#include "IdConfig.h"

#ifndef ECSID_H
#define ECSID_H

namespace ECSID {

	template<typename IdConfig>
	void Initialize() {
		if (_ecsIdRegistery == NULL) {
			_ecsIdRegistry = ECSIdRegistery(IdConfig)
		}
		// TODO: Add error if the _ecsIdRegistery has been initialized
	}
	std::type_index GetEntityIdType() {
		return _entityIdType;
	}

	std::type_index GetComponentIdType() {
		return _componentIdType;
	}

	namespace {

		ECSIdRegistery _ecsIdRegistry;

		std::type_index _entityIdType;
		std::type_index _componentIdType;
	}

};

#endif //ECSID_H
