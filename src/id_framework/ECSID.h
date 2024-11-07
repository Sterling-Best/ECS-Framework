#include <typeindex>

#include "ecs_id_registery.h"
#include "ecs_id_manager.h"

#ifndef ECSID_H
#define ECSID_H

namespace ECSID {

	template<typename idConfig>
	void Initialize() {
		_ecsIdManager = ECSIdMaanger();
		_ecsIdManager.Initialize<idConfig>();
	}

	std::type_index GetEntityIdType() {
		return _ecsIdManager;
	}

	std::type_index GetComponentIdType() {
		return _componentIdType;
	}

	namespace {
		ECSIdMaanger _ecsIdManger;
	}

};

#endif //ECSID_H
