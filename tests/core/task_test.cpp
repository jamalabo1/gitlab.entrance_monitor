//
// Created by jamal on 16/10/2022.
//
#include <core/task.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <utils/types.h>

#include "configurations_mock.h"
#include <core/standalone.h>

namespace {
//    using ::testing::_;
    using namespace ::testing;
//    using ::testing::Action;

    class TaskTestFixture : public ::testing::Test {
    protected:

        class TestTask : public core::Task {
        public:
            INJECT(TestTask()) = default;

            core::Task::TaskResult operator()() override {
                return TaskResult();
            }

            std::string name() const override {
                return utils::type_name(this);
            }
        };

        static fruit::Component<core::Task, core::IoContext> getRootComponent() {
            return fruit::createComponent()
                    .install(getMockConfigurationComponent)
                    .install(core::getIoContextComponent)
                    .bind<core::Task, TestTask>();
        }

    };


    TEST_F(TaskTestFixture, TaskSetupDefaultExecutorLoopsUntilTokenIsCanceled) {
        fruit::Injector injector(getRootComponent);

        auto ctx = injector.get<shared_ptr<core::IoContext>>();
        auto test = injector.get<core::Task *>();
        auto token = make_shared<core::CancellationToken>();

        auto run_options = test->setup(ctx, token);


        MockFunction<void()> cb;

        // 2. Set expectations on Call() method.
        EXPECT_CALL(cb, Call()).WillRepeatedly(Return());

        boost::asio::post(GET_BOOST_IO_CONTEXT(ctx), [&]() {
            // run the executor on this callback;
            run_options.executor(cb.AsStdFunction());
        });

        boost::asio::deadline_timer timer(GET_BOOST_IO_CONTEXT(ctx));

        timer.expires_from_now(boost::posix_time::seconds(2));
        timer.async_wait([&](const boost::system::error_code &) {
            // cancel the token.
            token->cancel();
        });

        // run the io-context
        core::run_io_context(ctx);
    }
}