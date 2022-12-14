//
// Created by root on 9/28/22.
//

#include "retry_policy_impl.h"


namespace core::retry {
    using fruit::createComponent;

    namespace impl {
        RetryPolicyImpl::RetryPolicyImpl(ASSISTED(Options) options, shared_ptr<IoContext> io_context)
                : timer_(GET_BOOST_IO_CONTEXT(io_context)),
                  options(options), failed_retry_count(0) {
        }

        void RetryPolicyImpl::ping() {
            failed_retry_count = 0;
            schedule_retry_handler();
        }

        void RetryPolicyImpl::schedule_retry_handler() {
            // this sets the expiration time to the retry_duration, and cancels any awaiting tasks.
            timer_.expires_from_now(options.retry_duration);
            // this is acts like nodejs `setTimeout`, it sets a function to be executed based on the retry_duration.
            timer_.async_wait([this](const boost::system::error_code &ec) {
                // check if didn't fail or expire.
                if (!ec.failed())
                    retry_handler();
            });
        }

        void RetryPolicyImpl::stop_stream_loop() {
            options.fail_handler();
        }

        void RetryPolicyImpl::retry_handler() {
            if (failed_retry_count > 10) {
                // stop the stream obtainer loop.
                stop_stream_loop();

                // cancel the timer.
                timer_.cancel();
                // exit the `retry_handler`
                return;
            }

            bool result = options.retry_handler();
            // check if the retry operation was successful.
            if (!result) {
                // it failed, so increase the count.
                failed_retry_count++;

                // and schedule another retry.
                return schedule_retry_handler();
            }

            // since the operation was successful, it pings the operation.
            return ping();
        }
    }

    RetryPolicyComponent getRetryPolicyComponent() {
        return createComponent()
                .bind<RetryPolicy, impl::RetryPolicyImpl>();
    }
}
