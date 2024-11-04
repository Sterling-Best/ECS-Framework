#ifndef SETTINGS_H
#define SETTINGS_H

#include <cstdint>

namespace IdConfig {
    // Switch the type here for compile-time configuration

    using ComponentIdType = unit32_t;
    using EntityIdType = unit32_t;



    namespace {
        // Switch to uint64_t or any other type if needed

        b ool _universalType;

        void _SameTypeCheck{
            if (ComponentIdType == EntityIdType) {
                _universalType == true
            }
        }

    }
}

#endif // SETTINGS_H