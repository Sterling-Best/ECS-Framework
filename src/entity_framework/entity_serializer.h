#include "entity.h"

#include "nlohmann/json.hpp"
using json = nlohmann::json;

class EntitySerializer {

    //Serialize
    std::string Serialize(Entity targetEntity) const {
        json j;

        // Serialize entityId
        j["entityId"] = targetEntity.entityId;

        // Serialize stateBitmask (assuming it can be converted to a string)
        j["stateBitmask"] = targetEntity.stateBitmask.to_string();

        // Serialize appliedComponents
        json componentsJson = json::array();
        for (const auto& [type, componentId] : targetEntity.appliedComponents) {
            componentsJson.push_back({
                {"type", type.name()},  // Store the name of the type
                {"componentId", componentId}
                });
        }
        j["appliedComponents"] = componentsJson;

        // Return the JSON as a string
        return j.dump();
    }

    // Deserialize: Reconstruct an Entity from a JSON string
    static Entity Deserialize(const std::string& data) {
        nlohmann::json j = nlohmann::json::parse(data);
        Entity entity;

        // Deserialize entityId
        entity.entityId = j["entityId"].get<EntityIdType>();

        // Deserialize stateBitmask
        entity.stateBitmask = Bitmask(j["stateBitmask"].get<std::string>());

        // Deserialize appliedComponents
        for (const auto& component : j["appliedComponents"]) {
            std::type_index type = std::type_index(typeid(component["type"].get<std::string>().c_str()));
            ComponentIdType componentId = component["componentId"].get<ComponentIdType>();
            entity.appliedComponents[type] = componentId;
        }

        return entity;
    }

};