//
// Created by jamal on 19/09/2022.
//

#include <gtest/gtest.h>

#include <core/cancellation_token.h>

#include <thread>

#include <boost/asio.hpp>

namespace {

    using namespace std;

    class CancellationTokenTestFixture : public ::testing::Test {

    };


    TEST_F(CancellationTokenTestFixture, CancellationTokenChangesStateOnCancel) {

        core::CancellationToken token;

        ASSERT_EQ(token.isActive(), core::CancellationToken::default_state);

        token.cancel();

        EXPECT_FALSE(token.isActive());
        EXPECT_TRUE(token.isCanceled());
    }

    TEST_F(CancellationTokenTestFixture, CanellationTokenCanStopThread) {

        core::CancellationToken token;

        ASSERT_TRUE(token.isActive());

        atomic_bool is_test_func_running = false;
        auto test_func = [&]() {
            while (token.isActive()) {
                if (!is_test_func_running) {
                    is_test_func_running = true;
                }
            }
            is_test_func_running = false;
        };

        ASSERT_FALSE(is_test_func_running);


        boost::asio::thread_pool pool;
        boost::asio::post(pool, test_func);

        boost::asio::deadline_timer t(pool, boost::posix_time::seconds(5));

        t.async_wait([&](const boost::system::error_code &ec){
            EXPECT_TRUE(is_test_func_running);
            token.cancel();
            pool.stop();
        });

        pool.join();

        EXPECT_TRUE(token.isCanceled());
        EXPECT_FALSE(is_test_func_running);

    }
}
