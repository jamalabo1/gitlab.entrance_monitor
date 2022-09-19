#pragma once

#ifndef CORE_QUEUE_FPS_HPP
#define CORE_QUEUE_FPS_HPP

#include <condition_variable>
#include <mutex>
#include <queue>
#include <opencv2/core.hpp>
#include <core/logging.h>

enum severity_level {
    trace
};

namespace core {

    template<typename T>
    class QueueFPS {
    private:
        cv::TickMeter tm;
        std::mutex mutex;
        boost::log::sources::logger logger;
    private:
        std::deque<T> queue;
        const int m_queue_max_size;

    public:
        explicit QueueFPS(int queue_max_size = 15) : queue(), counter(0), m_queue_max_size(queue_max_size), logger() {
            logger.add_attribute("QueueName",
                                 boost::log::attributes::constant<std::string>(typeid(this).name())
            );
        }

        void push(const T &entry) {
            BOOST_LOG_TRIVIAL(trace) << "requesting mutex lock";
            std::lock_guard<std::mutex> lock(mutex);
            BOOST_LOG_TRIVIAL(trace) << "pushing into _queue";

            // push to the back
            queue.push_back(entry);

            if (queue.size() > m_queue_max_size) {
                clear(true);
            }

            counter += 1;
            if (counter == 1) {
                // Start counting from a second frame (warmup).
                tm.reset();
                tm.start();
            }
        }

        T get() {
            BOOST_LOG_TRIVIAL(trace) << "waiting for mutex lock";
            std::lock_guard<std::mutex> lock(mutex);
            BOOST_LOG_TRIVIAL(trace) << "receiving item from _queue front";
            T entry = queue.front();
            BOOST_LOG_TRIVIAL(trace) << "popping received item from the _queue";

            // consume from the front
            queue.pop_front();
            BOOST_LOG_TRIVIAL(trace) << "returning received item";
            return entry;
        }

        bool empty() {
            return queue.empty();
        }

        size_t count() {
            return queue.size();
        }

        float getFPS() {
            tm.stop();
            double fps = counter / tm.getTimeSec();
            tm.start();
            return static_cast<float>(fps);
        }

        void clear(bool locked = false) {
            BOOST_LOG_TRIVIAL(trace) << "clearing queue";
            if (!locked) {
                std::lock_guard<std::mutex> lock(mutex);
            }

            size_t difference = queue.size() - m_queue_max_size;

            // since the consume process is done from the front and new values are pushed to the back, then when the queue is crowded, the front should be cleared.
            for (size_t i = 0; i < difference; i++) {
                queue.pop_front();
            }
        }

        unsigned int counter;

    };
}

#endif // CORE_QUEUE_FPS_HPP