#include <unordered_map>
#include <memory>

#include "iid_config.h"

class ECSIdRegistery {

public:

    // TODO: COvert to SIngleton

    // TODO: Add teh ability to receive and add IdConfigs from the Modules folders

    std::shared_ptr<IIdConfig> GetCurrentIdConfig() {
        return _currentIdConfig;
    }

    template<typename selectedIdConfig>
    void SetIdConfig() {
        auto it = _idConfigPool.find(typeid(selectedIdConfig));
        if (it != _idConfigPool.end()) {
            _currentIdConfig = it->second->Clone();
        } 
        else {
            // Handle the case where the config is not found
        }
    }

    // TODO: Add a method that collects all classes in internal and external modles folders and place it in the _idConfigPool at CompileTime

private:
    std::shared_ptr<IIdConfig> _currentIdConfig;
	std::unordered_map<std::type_index, std::unique_ptr<IIdConfig>> _idConfigPool;
	
}; 