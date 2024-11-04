#include <typeindex>

#include "ecs_id_registery.h"
#include "IdConfig.h"

#ifndef ECSID_H
#define ECSID_H

namespace ECSID {

	template<typename idConfig>
	void Initialize() {
		if (!_ecsIdRegistery) {
				_ecsIdRegistery = ECSIdRegistery();
				_ecsIdRegistery.SetIdConfig<idConfig>();
				_entityIdType = _ecsIdRegistery.GetCurrentIdConfig()->GetEntityIdType();
				_componentIdType = _ecsIdRegistery.GetCurrentIdConfig()->GetComponentIdType();
		}
		// TODO: Add error if the _ecsIdRegistery has been initialized
	}
	std::type_index GetEntityIdType() {
		return _entityIdType;
	}

	std::type_index GetComponentIdType() {
		return _componentIdType;
	}

	// TODO: Return what the next ID is suppose to be

	namespace {

		ECSIdRegistery _ecsIdRegistery;

		std::type_index _entityIdType;
		std::type_index _componentIdType;
	}

};

#endif //ECSID_H
