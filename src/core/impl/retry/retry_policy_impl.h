//
// Created by root on 9/28/22.
//

#ifndef ENTRANCE_MONITOR_V2_CORE_RETRY_POLICY_IMPL_H
#define ENTRANCE_MONITOR_V2_CORE_RETRY_POLICY_IMPL_H

#include <atomic>
#include <core/retry/policy.h>

namespace core::retry::impl {
    class RetryPolicyImpl : public RetryPolicy {
    private:
        Options options;
        boost::asio::deadline_timer timer_;
        std::atomic_int failed_retry_count;

    public:

        INJECT(RetryPolicyImpl(ASSISTED(Options), shared_ptr<IoContext>));

        void ping() override;

        void schedule_retry_handler();
        void retry_handler();
        void stop_stream_loop();
    };
}

#endif //ENTRANCE_MONITOR_V2_CORE_RETRY_POLICY_IMPL_H
