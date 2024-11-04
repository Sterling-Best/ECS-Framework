#include <typeindex>

#include "IdConfig.h"

namespace ECSID {


};

class ECSIDA {

public:

	ECSID(const ECSID&) = delete;
	ECSID& operator=(const ECSID&) = delete;

	// Public method to access the singleton instance
	static ECSID& GetInstance() {
		static ECSID instance; // Guaranteed to be destroyed, instantiated on first use
		return instance;
	}

	std::type_index GetEntityIdType() {
		return this->_entityIdType;
	}

	std::type_index GetComponentIdType() {
		return this->_componentIdType;
	}

private:

	ECSID()
		: _useUniversalId(true),
		_entityIdType(uint32_t),
		_componentIdType(uint64_t) {}

	bool _useUniversalId;

	std::type_index _entityIdType;
	std::type_index _componentIdType;
};