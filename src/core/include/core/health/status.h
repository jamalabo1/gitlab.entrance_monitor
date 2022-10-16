//
// Created by jamal on 28/09/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CORE_HEALTH_STATUS_H
#define ENTRANCE_MONITOR_V2_CORE_HEALTH_STATUS_H

namespace core::health {

    /// health status class for reporting the current state of the requested unit.
    struct Status {

        // default ok status.
        static Status Ok;
    };
}

#endif //ENTRANCE_MONITOR_V2_CORE_HEALTH_STATUS_H
