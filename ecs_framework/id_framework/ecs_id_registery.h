#include <unordered_map>

#include "iid_config.h"

class ECSIdRegistery {

public:

    template<typename selectedIdConfig>
    void SetIdConfig() {
        auto it = _idConfigPool.find(typeid(selectedIdConfig));
        if (it != _idConfigPool.end()) {
            _currentIdConfig = it->second; // Shared ownership, no copy made 
        else {
            // Handle the case where the config is not found
        }
    }

private:
	std::unique_ptr<IIdConfig> _currentIdConfig;
	std::unordered_map<std::type_index, std::unique_ptr<IIdConfig>> _idConfigPool;
	
}; 