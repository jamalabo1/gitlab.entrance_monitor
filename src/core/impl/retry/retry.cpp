//
// Created by root on 9/29/22.
//
#include <core/retry.h>

namespace core::retry {
    Components getRetryComponents() {
        return fruit::createComponent()
                .install(getIoContextComponent)
                .install(getRetryPolicyComponent);
    }
}
