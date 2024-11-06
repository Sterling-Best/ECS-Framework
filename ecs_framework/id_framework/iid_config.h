class IIdConfig {

public: 

    virtual ~IIdConfig() = default;

    std::type_index GetComponentIdType() const {
        return this->_componentIdType;
    }

    std::type_index GetEntityIdType() const {
        return this->_entityIdType;
    }

    /*The following Functions output a Type that is declare in the _entityIdType and _componentIdTYpe variables.
        we will not know what those are until a child class that defines them is created*/

    virtual auto NextEntityId() const = 0;
    virtual auto NextComponentId() const = 0;


protected:
    std::type_index _componentIdType;
    std::type_index _entityIdType;

};
