/**
* @file Entity.h
* @brief Defines the Entity struct used in the ECS framework.
*
* The Entity struct represents a core object in the ECS framework.It stores a unique
* entity ID, a state bitmask to track entity states, and a map of applied components.
*
* @author Sterling Best
* @date 2024 - 12 - 02
*/

#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <bitset>

#include "ankerl/unordered_dense.h"
#include "../id_framework/ECSID.h"

struct Entity {

	using EntityIdType = ECSID::EntityIdType;
	using ComponentIdType = ECSID::ComponentIdType;

	EntityIdType entityId; 
	std::bitset<32> stateBitmask;
	ankerl::unordered_dense::map <std::type_index, ComponentIdType > appliedCompoennts; /**< Maps component types to their unique IDs. Id Type determined by ECSID */

};

#endif //ENTITY_H