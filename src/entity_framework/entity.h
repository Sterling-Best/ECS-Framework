#include "ankerl/unordered_dense.h"
#include <ECSID.h>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

// TODO: Decide whether the components map should store the component id with a pointer direclt to the component. Or just store the type of component with the id, to be searched for in the componnt ID frameowrk. Thinking about doing the latter. 

struct Entity {

	using EntityIdType = ECSID::GetEntityIdType();
	using ComponentIdType = ECSID::GetComponentIdType();

	EntityIdType entityId;
	Bitmask stateBitmask;
	ankerl::unordered_dense::map < typeid, ComponentIdType > appliedCompoennts;

	// TODO: Serialize with JSON
    std::string Serialize() const {
        json j;

        // Serialize entityId
        j["entityId"] = entityId;

        // Serialize stateBitmask (assuming it can be converted to a string)
        j["stateBitmask"] = stateBitmask.to_string();

        // Serialize appliedComponents
        json componentsJson = json::array();
        for (const auto& [type, componentId] : appliedComponents) {
            componentsJson.push_back({
                {"type", type.name()},  // Store the name of the type
                {"componentId", componentId}
                });
        }
        j["appliedComponents"] = componentsJson;

        // Return the JSON as a string
        return j.dump();
    }

};