//
// Created by root on 9/28/22.
//

#ifndef ENTRANCE_MONITOR_V2_CORE_RETRY_H
#define ENTRANCE_MONITOR_V2_CORE_RETRY_H

#include <core/init.h>

#include "retry/policy.h"

// create try policy, with duration and executor.
// supply on_fail handler

namespace core::retry {
    EXPORT_MODULE(getRetryComponents, $RetryPolicy);
}

#endif //ENTRANCE_MONITOR_V2_CORE_RETRY_H
