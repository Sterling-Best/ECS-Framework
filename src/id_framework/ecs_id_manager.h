#include <typeindex>

#include "ecs_id_registery.h"
#include "iid_config.h"

class ECSIdMaanger {

public: 

	void ECSIdManger() {
		//_ecsIdRegistery = ECSIdRegistery();
	}

	//template<typename idConfig>
	//void Initiate() {
	//	_ecsIdRegistery.SetIdConfig<idConfig>();
	//	_iIdConfig = _ecsIdRegistery.GetCurrentIdConfig();
	//	_entityIdType = _iIdConfig.GetEntityIdType();
	//	_componentIdType = _iIdConfig.GetComponentIdType();
	//	if (!IdConfigTest) {
	//		//Report Error
	//	}
	//}

	//bool IdConfigTest() {
	//	std::type_index entityValue = std::type_index actualType(NextEntityId());
	//	std::type_index componentValue = std::type_index actualType(typeid(NextComponentId());
	//	if (GetEntityIdType() == entityValue
	//		&& GetComponentIdType() == componentValue) {
	//		return true;
	//	}
	//	return false;
	//}

	/* TODO: Test check to make sure that the output of
	IIdConfig class NextID matches the registered IDTypes*/


	std::type_index GetEntityIdType() {
		return typeid(uint64_t);
	}

	std::type_index GetComponentIdType() {
		return typeid(uint64_t);
	}

	auto NextEntityId() {
		return ++entityCounter;
	}

	auto NextComponentId() {
		return ++componentCounter;
	}

private:

	ECSIdRegistery _ecsIdRegistery;
	
	uint64_t entityCounter = 0;
	uint64_t componentCounter = 0;

	//IIdConfig _iIdConfig;
	
	/*std::type_index _entityIdType = uint64_t;
	std::type_index _componentIdType = uint;*/



};