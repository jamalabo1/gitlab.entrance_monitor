//
// Created by root on 9/28/22.
//

#ifndef ENTRANCE_MONITOR_V2_CORE_RETRY_POLICY_H
#define ENTRANCE_MONITOR_V2_CORE_RETRY_POLICY_H

#include <core/init.h>
#include <core/io_context.h>
#include <boost/function.hpp>
#include <boost/date_time.hpp>

namespace core::retry {
    class RetryPolicy {


    public:
        virtual ~RetryPolicy() = default;

        struct Options {
            boost::posix_time::time_duration retry_duration;
            boost::function<bool()> retry_handler;
            boost::function<void()> fail_handler;
        };

        // ping has to be called at-least one time to start the countdown
        /// ping function to reset the handling timer.
        virtual void ping() = 0;
    };


    using RetryPolicyFactory = MakeUniqueFactoryP(RetryPolicy, RetryPolicy::Options);
    using $RetryPolicy = $Exported<RetryPolicyFactory>;

    using RetryPolicyComponent = $RetryPolicy::Component<IoContext>;

    RetryPolicyComponent getRetryPolicyComponent();
}

#endif //ENTRANCE_MONITOR_V2_CORE_RETRY_POLICY_H
