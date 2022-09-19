//
// Created by jamal on 19/09/2022.
//
#include <gtest/gtest.h>
#include <core/queue_fps.h>
#include <boost/asio.hpp>

namespace {


    using namespace std;

    class QueueFpsTestFixture : public ::testing::Test {

    protected:
        template<typename T>
        size_t count_queue(core::QueueFPS<T> &queue) {
            return queue.count();
        }

        template<typename T>
        vector<T> queue_to_vector(core::QueueFPS<T> &queue) {
            vector<T> values;
            while (!queue.empty()) {
                values.template emplace_back(queue.get());
            }
            return values;
        }

    };

    TEST_F(QueueFpsTestFixture, QueueFpsInitializesEmpty) {
        core::QueueFPS<int> queue;

        ASSERT_TRUE(queue.empty());
    }

    TEST_F(QueueFpsTestFixture, QueueFpsPushAddsToQueue) {
        core::QueueFPS<int> queue;

        ASSERT_TRUE(queue.empty());

        int val = 10;
        queue.push(val);

        EXPECT_FALSE(queue.empty());

        EXPECT_EQ(queue.get(), val);
    }

    class QueueFpsTestFixtureFpsCounterTest : public QueueFpsTestFixture, public ::testing::WithParamInterface<int> {

    };

    TEST_P(QueueFpsTestFixtureFpsCounterTest, QueueFpsCounterReflectNearRealTimeNumbers) {
        core::QueueFPS<int> queue;
        static int trivial_value = 10;

        // (1000/x) *

        int target_fps_in_seconds = GetParam();


        int target_frame_per_ms = 1000 / target_fps_in_seconds;
        // used like this for int rounding.
        int rounded_target_fps = 1000 / target_frame_per_ms;

        boost::asio::io_context io;

        auto interval = boost::posix_time::milliseconds(target_frame_per_ms);
        boost::asio::deadline_timer pusher_timer(io, interval);


        auto push_func = [&queue]() {
            queue.push(trivial_value);
        };


        function<void(const boost::system::error_code &ec)> handler;

        handler = [&](const boost::system::error_code &ec) {
            push_func();
            pusher_timer.expires_from_now(interval);
            pusher_timer.async_wait(handler);
        };


        pusher_timer.expires_from_now(interval);
        pusher_timer.async_wait(handler);


        boost::asio::deadline_timer checker_timer(io, boost::posix_time::seconds(1));
        checker_timer.async_wait([&](const boost::system::error_code &ec) {
            int fps = queue.getFPS();

            // the difference between queue-fps and rounded target fps
            int fps_difference = abs(fps - rounded_target_fps);

            // willing to tolerate up to 5 fps.
            EXPECT_LE(fps_difference, 5);
            io.stop();
        });


        io.run();
    }

    class QueueFpsTestFixtureMaxSizeTest : public QueueFpsTestFixture, public ::testing::WithParamInterface<int> {

    };

    TEST_P(QueueFpsTestFixtureMaxSizeTest, QueueFpsCompliesWithMaxSize) {
        int max_size = GetParam();
        core::QueueFPS<int> queue(max_size);

        // [0, 1, 2, 3, 4];
        // [1, 2, 3, 4, 5];

        ASSERT_EQ(count_queue<int>(queue), 0);

        int overflow_count = 1;
        vector<int> values;
        for (int i = 0; i < (max_size + overflow_count); i++) {
            queue.push(i);
            values.emplace_back(i);
        }
        if (values.size() > max_size) {
            values.erase(values.begin(), values.begin() + overflow_count);
        }

        EXPECT_EQ(count_queue<int>(queue), max_size);
        EXPECT_EQ(queue_to_vector<int>(queue), values);
    }

    INSTANTIATE_TEST_SUITE_P(QueueFpsTests,
                             QueueFpsTestFixtureMaxSizeTest,
                             ::testing::Values(
                                     0, 1, 15, 30, 45, 60, 100
                             ));

    INSTANTIATE_TEST_SUITE_P(QueueFpsTests,
                             QueueFpsTestFixtureFpsCounterTest,
                             ::testing::Values(
                                     8, 12, 15, 30, 45, 60, 120
                             ));
}