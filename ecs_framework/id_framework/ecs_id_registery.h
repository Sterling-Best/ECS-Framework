#include <unordered_map>
#include <memory>

#include "iid_config.h"

class ECSIdRegistery {

    static ECSIdRegistry& Instance() {
        static ECSIdRegistry instance;
        return instance;
    }

    // Delete copy constructor and assignment operator to enforce singleton property
    ECSIdRegistry(const ECSIdRegistry&) = delete;
    ECSIdRegistry& operator=(const ECSIdRegistry&) = delete;

public:

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
            throw std::runtime_error("IdConfig not found in the pool");
        }
    }

    // TODO: Add a method that collects all classes in internal and external modles folders and place it in the _idConfigPool at CompileTime

private:

    explicit ECSIdRegistry() = default;  // Private constructor

    std::shared_ptr<IIdConfig> _currentIdConfig;
	std::unordered_map<std::type_index, std::unique_ptr<IIdConfig>> _idConfigPool;
	
}; 