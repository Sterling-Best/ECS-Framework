#include <typeindex>

#include "IdConfig.h"

#ifndef ECSID_H
#define ECSID_H

namespace ECSID {


	std::type_index GetEntityIdType() {
		return _entityIdType;
	}

	std::type_index GetComponentIdType() {
		return _componentIdType;
	}

	namespace {

		std::type_index _entityIdType;
		std::type_index _componentIdType;
	}

	// TODO: Create a ECIDConfigManager

};

#endif //ECSID_H
