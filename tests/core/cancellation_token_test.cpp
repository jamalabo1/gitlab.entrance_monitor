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

    TEST(CancellationTokenTest, CancellationTokenCompliesWithDefault) {
        core::CancellationToken token;

        ASSERT_EQ(token.isActive(), core::CancellationToken::default_state);
    }

    TEST(CancellationTokenTest, CancellationTokenChangesStateOnCancel) {

        core::CancellationToken token;

        ASSERT_TRUE(token.isActive());

        token.cancel();

        EXPECT_FALSE(token.isActive());
        EXPECT_TRUE(token.isCanceled());
    }


    TEST(CancellationTokenTest, CancellationTokenCanStopThread) {

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

        t.async_wait([&](const boost::system::error_code &ec) {
            EXPECT_TRUE(is_test_func_running);
            token.cancel();
            pool.stop();
        });

        pool.join();

        EXPECT_TRUE(token.isCanceled());
        EXPECT_FALSE(is_test_func_running);
    }

    TEST(CancellationTokenTest, CancellationTokenCanStopBlockingThread) {
        auto token = make_shared<core::CancellationToken>();

        ASSERT_TRUE(token->isActive());

        boost::asio::thread_pool io(2);
        boost::asio::deadline_timer worker_timer(io);
        boost::asio::deadline_timer cancel_timer(io);
        auto worker_duration = boost::posix_time::seconds(5);
        worker_timer.expires_from_now(worker_duration);

        atomic_bool waiting_for_timer = false;
        atomic_bool changed_state = false;
        atomic_bool quited_while = false;

        boost::asio::post(io, [&]() {
            while (token->isActive()) {
                waiting_for_timer = true;
                worker_timer.wait();
                changed_state = true;
            }
            quited_while = true;
        });

        // we can cancel the token here after running the task because it's not important how much the task lasted, what we want is to check if the while quits even before finishing the iteration.

        auto cancel_duration = worker_duration / 2;
        cancel_timer.expires_from_now(cancel_duration);
        cancel_timer.async_wait([&](const boost::system::error_code &ec) {
            token->cancel();
        });

        // wait for the io to finish running, because after that we can check the results.
        io.join();

        // if the quited_while is true and changed_state is false then this is the desired state that we are looking for.

        EXPECT_TRUE(waiting_for_timer);
        EXPECT_TRUE(quited_while);
        EXPECT_FALSE(changed_state);
    }
}
