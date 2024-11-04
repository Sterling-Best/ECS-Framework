class IIdConfig {

public: 

    virtual ~IIdConfig() = default;

    std::type_index GetComponentIdType() const {
        return this->_componentIdType;
    }

    std::type_index GetCEntityIDType() const {
        return this->_entityIdType;
    }

    // Pure virtual function making this an abstract class
    virtual void SetSequanceStartValue() const = 0;
    virtual void NetxIdInSequence() const = 0;

protected:
    std::type_index _componentIdType;
    std::type_index _entityIdType;

};
