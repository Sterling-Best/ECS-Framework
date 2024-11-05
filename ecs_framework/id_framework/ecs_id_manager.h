#include <typeindex>

#include "ecs_id_registery.h"
#include "iid_config.h"

class ECSIdMaanger {

public: 

	ECSIdMaanger() {
		_ecsIdRegistery = ECSIdRegistery();
	}

	template<typename idConfig>
	void Initiate() {
		_ecsIdRegistery.SetIdConfig<idConfig>();
		_iIdConfig = _ecsIdRegistery.GetCurrentIdConfig();
		_entityIdType = _iIdConfig.GetEntityIdType();
		_componentIdType = _iIdConfig.GetComponentIdType();
	}

	/* TODO: Test check to make sure that the output of
	IIdConfig class NextID matches the registered IDTypes*/


	std::type_index GetEntityIdType() {
		return _ecsIdManager;
	}

	std::type_index GetComponentIdType() {
		return _componentIdType;
	}

	auto NextEntityId() {
		return _iIdConfig.NextEntityId();
	}

	auto NextComponentId() {
		return _iIdConfig.NextComponentId()
	}

private:

	ECSIdRegistery _ecsIdRegistery;

	IIdConfig _iIdConfig;
	
	std::type_index _entityIdType;
	std::type_index _componentIdType;



};