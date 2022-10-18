//
// Created by jamal on 16/10/2022.
//
#include "retry/retry_policy_impl.h"

#include "configurations_mock.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace {
    using namespace ::testing;

    class RetryPolicyTestFixture : public ::testing::Test {

    protected:

        static fruit::Component<core::IoContext, core::retry::RetryPolicyFactory> getRootComponent() {
            return fruit::createComponent()
                    .install(getMockConfigurationComponent)
                    .install(core::getIoContextComponent)
                    .install(core::retry::getRetryPolicyComponent);
        }

    };

    TEST_F(RetryPolicyTestFixture, RetryPolicyCallsOnTimeout) {
        fruit::Injector injector(getRootComponent);

        auto factory = injector.get<core::retry::RetryPolicyFactory>();


        MockFunction<void()> fail_handler;
        MockFunction<bool()> retry_handler;

        auto options = core::retry::RetryPolicy::Options{
                .retry_duration = boost::posix_time::seconds(5),
                .retry_handler = retry_handler.AsStdFunction(),
                .fail_handler = fail_handler.AsStdFunction()
        };
        auto policy = factory(options);
        // initial ping
        policy->ping();

        // now we expect the retry_handler to be called 5 seconds from now.
//        EXPECT_CALL(retry_handler, Call()).After(1);

        core::run_io_context(ctx);
    }

}