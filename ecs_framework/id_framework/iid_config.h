class IIdConfig {

public: 

    virtual ~IIdConfig() = default;

    std::type_index GetComponentIdType() const {
        return this->_componentIdType;
    }

    std::type_index GetEntityIdType() const {
        return this->_entityIdType;
    }

    virtual _entityIdType NextEntityId() const = 0;
    virtual _componentIdType NextComponentId() const = 0;


protected:
    std::type_index _componentIdType;
    std::type_index _entityIdType;

};
