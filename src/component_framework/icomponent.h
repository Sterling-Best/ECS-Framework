// IComponent.h
#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include <cstdint>

struct IComponent {

    // Default  
    bool isActive;
    uint32_t componentID;
    uint32_t entityID;

    // Constructor
    IComponent(uint32_t targetComponentID, uint32_t targetEntityID) 
        : isActive(true), componentID(targetComponentID), entityID(targetEntityID) {}
};

#endif // ICOMPONENT_H