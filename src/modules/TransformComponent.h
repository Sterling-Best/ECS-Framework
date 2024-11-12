#include<cstdint> // for unint32_t
#include "../component_framework/icomponent.h" //Include IComponent struct defintion

struct TransformComponent: public IComponent {
	double x, y, z;

    // Default constructor
    TransformComponent() : IComponent(0, 0), x(0.0), y(0.0), z(0.0) {}

    TransformComponent(uint32_t targetComponentID, uint32_t targetEntityID, double xPosition, double yPosition, double zPosition)
        : IComponent(targetComponentID, targetEntityID), x(xPosition), y(yPosition), z(zPosition) {}
};