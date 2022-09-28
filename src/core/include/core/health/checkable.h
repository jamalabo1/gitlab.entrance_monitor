//
// Created by jamal on 28/09/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CORE_HEALTH_CHECKABLE_H
#define ENTRANCE_MONITOR_V2_CORE_HEALTH_CHECKABLE_H

#include "status.h"

namespace core::health {
    /// interface representing units that can be checked for health.
    class ICheckable {
    public:
        virtual Status health_check() const = 0;
    };
}

#endif //ENTRANCE_MONITOR_V2_CORE_HEALTH_CHECKABLE_H
