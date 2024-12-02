#include <typeindex>

#include "ecs_id_registery.h"
#include "ecs_id_manager.h"

#ifndef ECSID_H
#define ECSID_H

namespace ECSID {

	// TODO: Properly configure this with IdConfig
	using EntityIdType = uint64_t;
	using ComponentIdType = uint64_t;

	EntityIdType _counter = 0;

	template<typename idConfig>
	void Initialize() {
		_ecsIdManager = ECSIdManger();
		//_ecsIdManager.Initialize<idConfig>();
	}

	// TODO: Properly configure this with IdConfig
	std::type_index GetEntityIdType() {
		
		return _ecsIdManager.GetEntityIdType();
		//return typeid(_ecsIdManger.GetEntityIdType());
	}

	// TODO: Properly configure this with IdConfig
	std::type_index GetComponentIdType() { 
		return typeid(ComponentIdType);
		//return _ecsIdManger.GetComponentIdType();
	}

	EntityIdType NextEntityId() {
		return ++_counter;
	}

	EntityIdType NextComponentId() {
		return ++_counter;
	}

	ECSIdMaanger _ecsIdManager =  ECSIdManger();

};

#endif //ECSID_H
