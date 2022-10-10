//
// Created by root on 9/29/22.
//
#include <core/retry.h>

using fruit::createComponent;
using core::retry::Components;
using core::retry::getRetryPolicyComponent;

Components core::retry::getRetryComponents() {
    return createComponent()
        .install(getIoContextComponent)
        .install(getRetryPolicyComponent);
}